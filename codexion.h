/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safiraja <safiraja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 09:12:17 by safiraja          #+#    #+#             */
/*   Updated: 2026/10/17 15:42:47 by safiraja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <sys/time.h>
# include <time.h>

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
	int		cap;
}	t_heap;

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	int				is_taken;
	long			available_at;
	long			next_ticket;
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

int				ft_atoi_strict(const char *s, long *out);
int				parse_args(int argc, char **argv, t_config *cfg);
long			get_time_ms(struct timeval *t0);
int				init_sim(t_sim *sim);
void			destroy_dongles(t_sim *sim, int count);
void			destroy_coders(t_sim *sim, int count);
void			destroy_sim(t_sim *sim);
int				heap_less(const t_req *a, const t_req *b);
void			heap_swap(t_req *a, t_req *b);
int				heap_push(t_heap *h, t_req r);
const t_req		*heap_peek(const t_heap *h);
t_req			heap_pop(t_heap *h);
void			ms_to_abstime(long ms, struct timespec *ts);
void			smart_sleep(t_sim *sim, long ms);
int				is_stopped(t_sim *sim);
void			log_state(t_sim *sim, int id, const char *msg);
int				acquire_dongle(t_coder *c, t_dongle *d);
void			release_dongle(t_sim *sim, t_dongle *d);
void			*coder_routine(void *arg);
void			stop_sim(t_sim *sim, int burned_id);
void			*monitor_routine(void *arg);
int				run_simulation(t_sim *sim);

#endif
