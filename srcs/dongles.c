/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelamma <moelamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 10:30:34 by moelamma          #+#    #+#             */
/*   Updated: 2026/07/13 10:43:19 by moelamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	lock_two(t_dongle *a, t_dongle *b)
{
	if (a->id < b->id)
	{
		pthread_mutex_lock(&a->lock);
		pthread_mutex_lock(&b->lock);
	}
	else
	{
		pthread_mutex_lock(&b->lock);
		pthread_mutex_lock(&a->lock);
	}
}

void	take_dongles(t_coder *coder)
{
	lock_two(coder->left, coder->right);
}

void	put_dongles(t_coder *coder)
{
	pthread_mutex_unlock(&coder->left->lock);
	pthread_mutex_unlock(&coder->right->lock);
}
