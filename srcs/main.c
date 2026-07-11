/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelamma <moelamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 16:44:25 by moelamma          #+#    #+#             */
/*   Updated: 2026/07/11 16:54:08 by moelamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_args	args;
	t_sim	sim;

	if (!parse_args(argc, argv, &args))
		return (1);
	if (!init_sim(&args, &sim))
	{
		free_sim(&sim);
		return (1);
	}
	print_sim(&sim);
	free_sim(&sim);
	return (0);
}
