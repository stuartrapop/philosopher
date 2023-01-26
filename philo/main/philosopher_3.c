/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:07:29 by srapopor          #+#    #+#             */
/*   Updated: 2023/01/26 15:56:55 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_eating_time(t_ph *phs, int ph_number, int *pass_cycle_test)
{
	struct timeval	now;
	long			ts;
	int				eat_time;
	int				num_time_eaten;

	pthread_mutex_lock(&phs[ph_number].eat_mutex);
	gettimeofday(&now, NULL);
	ts = time_ms(now, phs[0].game->start);
	eat_time = phs[ph_number].eat;
	pthread_mutex_unlock(&phs[ph_number].eat_mutex);
	usleep(50);
	if ((ts - eat_time) > phs[0].game->t_die)
	{
		pri_mut(&(phs[0].game->print), "%d %d has died\n", ts, ph_number + 1);
		set_stop_printing(phs);
		return (1);
	}
	pthread_mutex_lock(&phs[ph_number].eat_mutex);
	num_time_eaten = phs[ph_number].num_times_eaten;
	if (num_time_eaten < phs[0].game->num_eat)
		*pass_cycle_test = 0;
	pthread_mutex_unlock(&phs[ph_number].eat_mutex);
	usleep(50);
	return (0);
}

void	set_stop_printing(t_ph *phs)
{
	int	index;

	index = 0;
	while (index < (phs[0].game->number_phs))
	{
		pthread_mutex_lock(&phs[index].eat_mutex);
		phs[index].stop_printing = 1;
		pthread_mutex_unlock(&phs[index].eat_mutex);
		index++;
	}
}
