/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safiraja <safiraja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 09:39:16 by safiraja          #+#    #+#             */
/*   Updated: 2026/10/17 15:42:36 by safiraja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static t_req	make_req(t_coder *c, t_dongle *d)
{
	t_req	r;

	r.coder_id = c->id;
	if (c->sim->cfg.is_edf)
		r.key = c->last_compile_start + c->sim->cfg.t_burnout;
	else
		r.key = d->next_ticket++;
	return (r);
}

static void	wait_until(t_dongle *d, long ms)
{
	struct timespec	ts;

	ms_to_abstime(ms, &ts);
	pthread_cond_timedwait(&d->cond, &d->mutex, &ts);
}

static int	wait_turn(t_coder *c, t_dongle *d)
{
	long	now;

	while (!is_stopped(c->sim))
	{
		now = get_time_ms(&c->sim->t0);
		if (heap_peek(&d->queue)->coder_id == c->id && !d->is_taken)
		{
			if (now >= d->available_at)
				return (0);
			wait_until(d, d->available_at - now);
		}
		else
			pthread_cond_wait(&d->cond, &d->mutex);
	}
	return (-1);
}

int	acquire_dongle(t_coder *c, t_dongle *d)
{
	pthread_mutex_lock(&d->mutex);
	heap_push(&d->queue, make_req(c, d));
	if (wait_turn(c, d) != 0)
	{
		pthread_mutex_unlock(&d->mutex);
		return (-1);
	}
	heap_pop(&d->queue);
	d->is_taken = 1;
	log_state(c->sim, c->id, "has taken a dongle");
	pthread_mutex_unlock(&d->mutex);
	return (0);
}

void	release_dongle(t_sim *sim, t_dongle *d)
{
	pthread_mutex_lock(&d->mutex);
	d->is_taken = 0;
	d->available_at = get_time_ms(&sim->t0) + sim->cfg.cooldown;
	pthread_cond_broadcast(&d->cond);
	pthread_mutex_unlock(&d->mutex);
}
