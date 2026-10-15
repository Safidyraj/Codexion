/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safiraja <safiraja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 09:39:55 by safiraja          #+#    #+#             */
/*   Updated: 2026/09/22 09:11:44 by safiraja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <string.h>
#include "codexion.h"

static int	parse_scheduler(const char *s, int *is_edf)
{
	if (strcmp(s, "fifo") == 0)
		*is_edf = 0;
	else if (strcmp(s, "edf") == 0)
		*is_edf = 1;
	else
		return (-1);
	return (0);
}

static int	check_values(long *v)
{
	if (v[0] < 1 || v[0] > INT_MAX)
		return (-1);
	if (v[1] < 1 || v[2] < 1)
		return (-1);
	if (v[5] < 1 || v[5] > INT_MAX)
		return (-1);
	return (0);
}

int	parse_args(int argc, char **argv, t_config *cfg)
{
	long	v[7];
	int		i;

	if (argc != 9)
		return (-1);
	i = 0;
	while (i < 7)
	{
		if (ft_atoi_strict(argv[i + 1], &v[i]) != 0)
			return (-1);
		i++;
	}
	if (check_values(v) != 0 || parse_scheduler(argv[8], &cfg->is_edf) != 0)
		return (-1);
	cfg->nb_coders = (int)v[0];
	cfg->t_burnout = v[1];
	cfg->t_compile = v[2];
	cfg->t_debug = v[3];
	cfg->t_refactor = v[4];
	cfg->nb_compiles_required = (int)v[5];
	cfg->cooldown = v[6];
	return (0);
}
