/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safiraja <safiraja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 09:39:16 by safiraja          #+#    #+#             */
/*   Updated: 2026/10/17 15:42:24 by safiraja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "codexion.h"

long	get_time_ms(struct timeval *t0)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - t0->tv_sec) * 1000
		+ (now.tv_usec - t0->tv_usec) / 1000);
}

void	ms_to_abstime(long ms, struct timespec *ts)
{
	clock_gettime(CLOCK_REALTIME, ts);
	ts->tv_sec += ms / 1000;
	ts->tv_nsec += (ms % 1000) * 1000000L;
	if (ts->tv_nsec >= 1000000000L)
	{
		ts->tv_sec++;
		ts->tv_nsec -= 1000000000L;
	}
}

void	smart_sleep(t_sim *sim, long ms)
{
	long	end;

	end = get_time_ms(&sim->t0) + ms;
	while (!is_stopped(sim) && get_time_ms(&sim->t0) < end)
		usleep(500);
}
