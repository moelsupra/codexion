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

#include "codexion.h"

long	get_elapsed_ms(t_sim *sim)
{
	struct timeval	now;
	long			ms;

	gettimeofday(&now, NULL);
	ms = (now.tv_sec - sim->start_time.tv_sec) * 1000;
	ms += (now.tv_usec - sim->start_time.tv_usec) / 1000;

	return (ms);
}

void	log_state(t_sim *sim, int coder_id, const char *msg)
{
	long	ts;

	pthread_mutex_lock(&sim->log_lock);
	ts = get_elapsed_ms(sim);
	printf("%ld %d %s", ts, coder_id, msg);
	pthread_mutex_unlock(&sim->log_lock);
}