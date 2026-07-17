/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelamma <moelamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 15:55:21 by moelamma          #+#    #+#             */
/*   Updated: 2026/07/13 11:29:24 by moelamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_args
{
	int		number_of_coders;
	long	time_to_burnout;
	long	time_to_compile;
	long	time_to_debug;
	long	time_to_refactor;
	int		number_of_compiles_required;
	long	dongle_cooldown;
	int		scheduler;
}	t_args;

int		parse_args(int argc, char **argv, t_args *args);

typedef struct s_dongle
{
	int				id;
	pthread_mutex_t	lock;
}	t_dongle;

typedef struct s_sim	t_sim;

typedef struct s_coder
{
	int			id;
	t_dongle	*left;
	t_dongle	*right;
	int			compiles_done;
	pthread_t	thread;
	t_sim		*sim;

}	t_coder;

typedef struct s_sim
{
	t_args			args;
	t_dongle		*dongles;
	t_coder			*coders;
	struct timeval	start_time;
	pthread_mutex_t	log_lock;
}	t_sim;

int		init_sim(t_args *args, t_sim *sim);
void	free_sim(t_sim *sim);
void	print_sim(t_sim *sim);

// Threads

int		start_coders(t_sim *sim);
void	join_coders(t_sim *sim);

void	take_dongles(t_coder *coder);
void	put_dongles(t_coder *coder);

long	get_elapsed_ms(t_sim *sim);
void	log_state(t_sim *sim, int coder_id, const char *msg);
#endif