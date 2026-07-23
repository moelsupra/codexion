/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loggin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelamma <moelamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:00:56 by moelamma          #+#    #+#             */
/*   Updated: 2026/07/24 00:16:39 by moelamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	get_elapsed_ms(t_sim *sim)
{
	struct timeval	now;
	long			sec;
	long			usec;

	gettimeofday(&now, NULL);
	sec = (now.tv_sec - sim->start_time.tv_sec);
	usec = (now.tv_usec - sim->start_time.tv_usec);
	if (usec < 0)
	{
		sec -= 1;
		usec += 1000000;
	}
	return ((sec * 1000) + (usec / 1000));
}

void	log_state(t_sim *sim, int coder_id, const char *msg)
{
	long	ts;

	pthread_mutex_lock(&sim->log_lock);
	ts = get_elapsed_ms(sim);
	printf("%ld %d %s\n", ts, coder_id, msg);
	pthread_mutex_unlock(&sim->log_lock);
}