/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelamma <moelamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 15:55:21 by moelamma          #+#    #+#             */
/*   Updated: 2026/07/11 13:02:04 by moelamma         ###   ########.fr       */
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
	int	id;	
}	t_dongle;

typedef struct s_coder
{
	int			id;
	t_dongle	*left;
	t_dongle	*right;
	int			compiles_done;
}	t_coder;

typedef struct s_sim
{
	t_args		args;
	t_dongle	*dongles;
	t_coder		*coders;
}	t_sim;

int		init_sim(t_args *args, t_sim *sim);
void	free_sim(t_sim *sim);
void	print_sim(t_sim *sim);
#endif