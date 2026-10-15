/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safiraja <safiraja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 09:12:17 by safiraja          #+#    #+#             */
/*   Updated: 2026/09/22 13:12:37 by safiraja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <sys/time.h>

typedef struct s_config
{
	int		nb_coders;
	long	t_burnout;
	long	t_compile;
	long	t_debug;
	long	t_refactor;
	int		nb_compiles_required;
	long	cooldown;
	int		is_edf;
}	t_config;

int		ft_atoi_strict(const char *s, long *out);
int		parse_args(int argc, char **argv, t_config *cfg);
long	get_time_ms(struct timeval *t0);

#endif
