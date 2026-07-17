/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelamma <moelamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 17:19:54 by moelamma          #+#    #+#             */
/*   Updated: 2026/07/12 19:58:43 by moelamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	*coder_routine(void *arg)
{
	t_coder	*coder;
	int		n;

	coder = (t_coder *)arg;
	n = 0;
	while (n < 3)
	{
		take_dongles(coder);
		log_state(coder->sim, coder->id, "has taken a dongle");
		log_state(coder->sim, coder->id, "is compiling");
		usleep(50000);
		put_dongles(coder);
		n++;
	}

	return (NULL);
}

int	start_coders(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->args.number_of_coders)
	{
		
		if (pthread_create(&sim->coders[i].thread, NULL,
			coder_routine, &sim->coders[i]) != 0)
			{
				printf("from start_coders %d\n", i);
				fprintf(stderr, "Error: pthread_create failed\n");
				return (0);
			}
			i++;
			printf("from start_coders %d\n", i);
	}
	printf("from start_coders \n");
	return (1);
}

void	join_coders(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->args.number_of_coders)
	{
		pthread_join(sim->coders[i].thread, NULL);
		i++;
	}
}
