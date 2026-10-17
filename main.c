/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safiraja <safiraja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 09:39:16 by safiraja          #+#    #+#             */
/*   Updated: 2026/10/17 15:42:27 by safiraja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "codexion.h"

int	main(int argc, char **argv)
{
	t_sim	sim;
	int		ret;

	if (parse_args(argc, argv, &sim.cfg) != 0)
	{
		fprintf(stderr, "Usage: %s number_of_coders time_to_burnout "
			"time_to_compile time_to_debug time_to_refactor "
			"number_of_compiles_required dongle_cooldown "
			"scheduler(fifo|edf)\n", argv[0]);
		return (1);
	}
	if (init_sim(&sim) != 0)
	{
		fprintf(stderr, "Error: initialization failed\n");
		return (1);
	}
	ret = run_simulation(&sim);
	destroy_sim(&sim);
	return (ret != 0);
}
