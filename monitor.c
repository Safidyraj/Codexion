/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safiraja <safiraja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 09:39:16 by safiraja          #+#    #+#             */
/*   Updated: 2026/09/22 09:12:11 by safiraja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "codexion.h"

static void	wake_all(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->cfg.nb_coders)
	{
		pthread_mutex_lock(&sim->dongles[i].mutex);
		pthread_cond_broadcast(&sim->dongles[i].cond);
		pthread_mutex_unlock(&sim->dongles[i].mutex);
		i++;
	}
}

void	stop_sim(t_sim *sim, int burned_id)
{
	pthread_mutex_lock(&sim->log_mutex);
	pthread_mutex_lock(&sim->stop_mutex);
	if (!sim->stop)
	{
		sim->stop = 1;
		if (burned_id > 0)
			printf("%ld %d burned out\n", get_time_ms(&sim->t0), burned_id);
	}
	pthread_mutex_unlock(&sim->stop_mutex);
	pthread_mutex_unlock(&sim->log_mutex);
	wake_all(sim);
}

static int	check_burnout(t_sim *sim)
{
	int		i;
	long	last;

	i = 0;
	while (i < sim->cfg.nb_coders)
	{
		pthread_mutex_lock(&sim->coders[i].mutex);
		last = sim->coders[i].last_compile_start;
		pthread_mutex_unlock(&sim->coders[i].mutex);
		if (get_time_ms(&sim->t0) - last > sim->cfg.t_burnout)
		{
			stop_sim(sim, sim->coders[i].id);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	all_done(t_sim *sim)
{
	int	i;
	int	count;

	i = 0;
	while (i < sim->cfg.nb_coders)
	{
		pthread_mutex_lock(&sim->coders[i].mutex);
		count = sim->coders[i].nb_compiles;
		pthread_mutex_unlock(&sim->coders[i].mutex);
		if (count < sim->cfg.nb_compiles_required)
			return (0);
		i++;
	}
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_sim	*sim;

	sim = (t_sim *)arg;
	while (!is_stopped(sim))
	{
		if (check_burnout(sim))
			return (NULL);
		if (all_done(sim))
		{
			stop_sim(sim, 0);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
