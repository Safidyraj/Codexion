/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safiraja <safiraja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 09:39:16 by safiraja          #+#    #+#             */
/*   Updated: 2026/10/17 15:42:23 by safiraja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	join_coders(t_sim *sim, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(sim->coders[i].thread, NULL);
		i++;
	}
}

static int	abort_start(t_sim *sim, int count)
{
	stop_sim(sim, 0);
	join_coders(sim, count);
	return (-1);
}

static int	start_coders(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->cfg.nb_coders)
	{
		sim->coders[i].last_compile_start = 0;
		sim->coders[i].nb_compiles = 0;
		if (pthread_create(&sim->coders[i].thread, NULL,
				coder_routine, &sim->coders[i]) != 0)
			return (abort_start(sim, i));
		i++;
	}
	return (0);
}

int	run_simulation(t_sim *sim)
{
	pthread_t	monitor;

	gettimeofday(&sim->t0, NULL);
	if (start_coders(sim) != 0)
		return (-1);
	if (pthread_create(&monitor, NULL, monitor_routine, sim) != 0)
		return (abort_start(sim, sim->cfg.nb_coders));
	pthread_join(monitor, NULL);
	join_coders(sim, sim->cfg.nb_coders);
	return (0);
}
