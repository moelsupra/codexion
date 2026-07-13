/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loggin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelamma <moelamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:00:56 by moelamma          #+#    #+#             */
/*   Updated: 2026/07/13 13:15:02 by moelamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

long	get_elapsed_ms(t_sim *sim)
{
	struct timeval	now;
	long			ms;

	gettimeofday(&now, NULL);
	ms = (now.tv_sec - sim->start_time.tv_sec) * 1000;
	printf("tv sec ms : %ld\n", ms);
	ms += (now.tv_usec - sim->start_time.tv_usec) / 1000;
	printf("tv usec ms : %ld\n", ms);

	return (ms);
}

int	main(void)
{
	struct timeval	now;
	long			ms;

	ms = 0;
	gettimeofday(&now, NULL);

}
// void	log_state(t_sim *sim, int coder_id, const char *msg);