/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safiraja <safiraja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 09:39:16 by safiraja          #+#    #+#             */
/*   Updated: 2026/09/22 09:12:11 by safiraja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "codexion.h"

int	main(int argc, char **argv)
{
	t_config		cfg;
	struct timeval	t0;

	if (parse_args(argc, argv, &cfg) != 0)
	{
		fprintf(stderr, "Usage: %s number_of_coders time_to_burnout "
			"time_to_compile time_to_debug time_to_refactor "
			"number_of_compiles_required dongle_cooldown "
			"scheduler(fifo|edf)\n", argv[0]);
		return (1);
	}
	gettimeofday(&t0, NULL);
	return (0);
}
