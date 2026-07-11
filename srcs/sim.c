/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelamma <moelamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 11:49:34 by moelamma          #+#    #+#             */
/*   Updated: 2026/07/11 16:53:57 by moelamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	init_sim(t_args *args, t_sim *sim)
{
	int	nb_coders;
	int	i;

	sim->args = *args;
	nb_coders = sim->args.number_of_coders;
	sim->dongles = malloc(sizeof(t_dongle) * nb_coders);
	sim->coders = malloc(sizeof(t_coder) * nb_coders);
	if (!sim->dongles || !sim->coders)
		return (0);
	i = 0;
	while (i < nb_coders)
	{
		sim->dongles[i].id = i;
		sim->coders[i].id = i + 1;
		sim->coders[i].compiles_done = 0;
		sim->coders[i].right = &sim->dongles[i];
		sim->coders[i].left = &sim->dongles[(i - 1 + nb_coders) % nb_coders];
		i++;
	}
	return (1);
}

void	print_sim(t_sim *sim)
{
	int	i;

	printf("=== SIMULATION ===\n");
	printf("Number of coders: %d\n", sim->args.number_of_coders);
	i = 0;
	while (i < sim->args.number_of_coders)
	{
		printf("coder %d: right=dongle(%d) left=dongle(%d)\n",
			sim->coders[i].id,
			sim->coders[i].right->id,
			sim->coders[i].left->id);
		i++;
	}
}

void	free_sim(t_sim *sim)
{
	if (sim->dongles)
	{
		free(sim->dongles);
		sim->dongles = NULL;
	}
	if (sim->coders)
	{
		free(sim->coders);
		sim->coders = NULL;
	}
}
