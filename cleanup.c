/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safiraja <safiraja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 09:39:16 by safiraja          #+#    #+#             */
/*   Updated: 2026/09/22 09:12:11 by safiraja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "codexion.h"

void	destroy_dongles(t_sim *sim, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_cond_destroy(&sim->dongles[i].cond);
		pthread_mutex_destroy(&sim->dongles[i].mutex);
		free(sim->dongles[i].queue.data);
		i++;
	}
	free(sim->dongles);
	sim->dongles = NULL;
}

void	destroy_coders(t_sim *sim, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&sim->coders[i].mutex);
		i++;
	}
	free(sim->coders);
	sim->coders = NULL;
}

void	destroy_sim(t_sim *sim)
{
	pthread_mutex_destroy(&sim->stop_mutex);
	pthread_mutex_destroy(&sim->log_mutex);
	destroy_coders(sim, sim->cfg.nb_coders);
	destroy_dongles(sim, sim->cfg.nb_coders);
}
