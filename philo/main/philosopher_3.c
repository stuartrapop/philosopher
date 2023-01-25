/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:07:29 by srapopor          #+#    #+#             */
/*   Updated: 2023/01/25 20:45:18 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_eating_time(t_ph *phs, int ph_number, int *pass_cycle_test)
{
	struct timeval	now;
	long			ts;
	int				eat_time;

	pthread_mutex_lock(&phs[0].game->monitor);
	gettimeofday(&now, NULL);
	ts = time_ms(now, phs[0].game->start);
	eat_time = phs[ph_number].eat;
	pthread_mutex_unlock(&phs[0].game->monitor);
	if ((ts - phs[ph_number].eat) > phs[0].game->t_die)
	{
		pthread_mutex_lock(&phs[0].game->monitor);
		phs[ph_number].game->is_over = 1;
		pri_mut(&(phs[0].game->print), "%d %d has died\n", ts, ph_number + 1);
		pthread_mutex_unlock(&phs[0].game->monitor);
		return (1);
	}
	pthread_mutex_lock(&phs[0].game->monitor);
	if (phs[ph_number].num_times_eaten < phs[0].game->num_eat)
				*pass_cycle_test = 0;
	pthread_mutex_unlock(&phs[0].game->monitor);
	return (0);
}
