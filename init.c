/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safiraja <safiraja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 09:39:16 by safiraja          #+#    #+#             */
/*   Updated: 2026/09/22 09:12:11 by safiraja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "codexion.h"

static int	init_one_dongle(t_dongle *d)
{
	d->is_taken = 0;
	d->available_at = 0;
	d->queue.size = 0;
	d->queue.data = malloc(sizeof(t_req) * 2);
	if (!d->queue.data)
		return (-1);
	if (pthread_mutex_init(&d->mutex, NULL) != 0)
	{
		free(d->queue.data);
		return (-1);
	}
	if (pthread_cond_init(&d->cond, NULL) != 0)
	{
		pthread_mutex_destroy(&d->mutex);
		free(d->queue.data);
		return (-1);
	}
	return (0);
}

static int	init_dongles(t_sim *sim)
{
	int	i;

	sim->dongles = malloc(sizeof(t_dongle) * sim->cfg.nb_coders);
	if (!sim->dongles)
		return (-1);
	i = 0;
	while (i < sim->cfg.nb_coders)
	{
		if (init_one_dongle(&sim->dongles[i]) != 0)
		{
			destroy_dongles(sim, i);
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	init_one_coder(t_sim *sim, int i)
{
	t_coder	*c;

	c = &sim->coders[i];
	c->id = i + 1;
	c->left = &sim->dongles[i];
	c->right = &sim->dongles[(i + 1) % sim->cfg.nb_coders];
	c->last_compile_start = 0;
	c->nb_compiles = 0;
	c->sim = sim;
	return (pthread_mutex_init(&c->mutex, NULL));
}

static int	init_coders(t_sim *sim)
{
	int	i;

	sim->coders = malloc(sizeof(t_coder) * sim->cfg.nb_coders);
	if (!sim->coders)
		return (-1);
	i = 0;
	while (i < sim->cfg.nb_coders)
	{
		if (init_one_coder(sim, i) != 0)
		{
			destroy_coders(sim, i);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	init_sim(t_sim *sim)
{
	sim->stop = 0;
	sim->dongles = NULL;
	sim->coders = NULL;
	if (init_dongles(sim) != 0)
		return (-1);
	if (init_coders(sim) != 0)
	{
		destroy_dongles(sim, sim->cfg.nb_coders);
		return (-1);
	}
	if (pthread_mutex_init(&sim->log_mutex, NULL) != 0
		|| pthread_mutex_init(&sim->stop_mutex, NULL) != 0)
	{
		destroy_coders(sim, sim->cfg.nb_coders);
		destroy_dongles(sim, sim->cfg.nb_coders);
		return (-1);
	}
	return (0);
}
