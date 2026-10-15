/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safiraja <safiraja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 08:38:11 by safiraja          #+#    #+#             */
/*   Updated: 2026/10/13 08:38:14 by safiraja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	run_simulation(t_sim *sim)
{
	int			i;
	pthread_t	monitor;

	gettimeofday(&sim->t0, NULL);
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
	if (pthread_create(&monitor, NULL, monitor_routine, sim) != 0)
		return (abort_start(sim, sim->cfg.nb_coders));
	pthread_join(monitor, NULL);
	join_coders(sim, sim->cfg.nb_coders);
	return (0);
}