/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safiraja <safiraja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 09:12:17 by safiraja          #+#    #+#             */
/*   Updated: 2026/10/13 08:18:33 by safiraja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <sys/time.h>

typedef struct s_sim	t_sim;

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

typedef struct s_req
{
	int		coder_id;
	long	key;
}	t_req;

typedef struct s_heap
{
	t_req	*data;
	int		size;
}	t_heap;

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	int				is_taken;
	long			available_at;
	t_heap			queue;
}	t_dongle;

typedef struct s_coder
{
	int				id;
	pthread_t		thread;
	t_dongle		*left;
	t_dongle		*right;
	long			last_compile_start;
	int				nb_compiles;
	pthread_mutex_t	mutex;
	t_sim			*sim;
}	t_coder;

struct s_sim
{
	t_config		cfg;
	struct timeval	t0;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	stop_mutex;
	int				stop;
};

int		ft_atoi_strict(const char *s, long *out);
int		parse_args(int argc, char **argv, t_config *cfg);
long	get_time_ms(struct timeval *t0);

#endif