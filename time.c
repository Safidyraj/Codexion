/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safiraja <safiraja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 09:40:00 by safiraja          #+#    #+#             */
/*   Updated: 2026/10/13 09:38:35 by safiraja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	get_time_ms(struct timeval *t0)
{
   struct	timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - t0->tv_sec) * 1000
		+ (now.tv_usec - t0->tv_usec) / 1000); 
}