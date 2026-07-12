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

	coder = (t_coder *)arg;
	printf("Coder %d Thread created succesfully !!!\n", coder->id);
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
			fprintf(stderr, "Error: pthread_create failed\n");
			return (0);
		}
		i++;
	}
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
