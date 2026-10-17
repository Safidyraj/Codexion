/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safiraja <safiraja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 09:39:16 by safiraja          #+#    #+#             */
/*   Updated: 2026/10/17 15:42:39 by safiraja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "codexion.h"

static int	take_dongles(t_coder *c)
{
	t_dongle	*first;
	t_dongle	*second;

	first = c->left;
	second = c->right;
	if (c->right < c->left)
	{
		first = c->right;
		second = c->left;
	}
	if (acquire_dongle(c, first) != 0)
		return (-1);
	if (acquire_dongle(c, second) != 0)
		return (-1);
	return (0);
}

static void	do_compile(t_coder *c)
{
	t_sim	*sim;

	sim = c->sim;
	pthread_mutex_lock(&c->mutex);
	c->last_compile_start = get_time_ms(&sim->t0);
	pthread_mutex_unlock(&c->mutex);
	log_state(sim, c->id, "is compiling");
	smart_sleep(sim, sim->cfg.t_compile);
	pthread_mutex_lock(&c->mutex);
	c->nb_compiles++;
	pthread_mutex_unlock(&c->mutex);
	release_dongle(sim, c->left);
	release_dongle(sim, c->right);
}

static void	*lone_coder(t_coder *c)
{
	log_state(c->sim, c->id, "has taken a dongle");
	while (!is_stopped(c->sim))
		usleep(1000);
	return (NULL);
}

void	*coder_routine(void *arg)
{
	t_coder	*c;

	c = (t_coder *)arg;
	if (c->sim->cfg.nb_coders == 1)
		return (lone_coder(c));
	while (!is_stopped(c->sim))
	{
		if (take_dongles(c) != 0)
			break ;
		do_compile(c);
		log_state(c->sim, c->id, "is debugging");
		smart_sleep(c->sim, c->sim->cfg.t_debug);
		log_state(c->sim, c->id, "is refactoring");
		smart_sleep(c->sim, c->sim->cfg.t_refactor);
	}
	return (NULL);
}
