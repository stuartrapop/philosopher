/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:28:03 by srapopor          #+#    #+#             */
/*   Updated: 2023/01/25 15:34:26 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	get_fork(t_ph *ph, int fork)
{
	struct timeval	now;

	pthread_mutex_lock(&(ph->phs[fork].fork));
	gettimeofday(&now, NULL);
	if (!ph->game->is_over)
		pri_mut(&(ph->game->print), "%d %d has taken a fork\n", \
			time_ms(now, ph->game->start), ph->num);
	return (0);
}

int	eat_and_release(t_ph *ph, int fork1, int fork2)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	ph->eat = time_ms(now, ph->game->start);
	ph->num_times_eaten++;
	if (!ph->game->is_over)
		pri_mut(&(ph->game->print), "%d %d is eating\n", ph->eat, ph->num);
	while ((time_ms(now, ph->game->start) - ph->eat) < ph->game->t_eat)
		gettimeofday(&now, NULL);
	pthread_mutex_unlock(&(ph->phs[fork1].fork));
	pthread_mutex_unlock(&(ph->phs[fork2].fork));
	return (0);
}

int	ph_sleep(t_ph *ph)
{
	struct timeval	now;

	usleep(1000);
	gettimeofday(&now, NULL);
	ph->sleep = time_ms(now, ph->game->start);
	if (!ph->game->is_over)
		pri_mut(&(ph->game->print), "%d %d is sleeping\n", ph->sleep, ph->num);
	while ((time_ms(now, ph->game->start) - ph->sleep) < ph->game->t_sleep)
		gettimeofday(&now, NULL);
	return (0);
}

int	ph_life_cycle(t_ph *ph)
{
	struct timeval	now;
	int				fork1;
	int				fork2;

	if (ph->num == 0)
		fork1 = ph->game->number_phs;
	else
		fork1 = ph->num - 1;
	fork2 = ph->num;
	while (1)
	{
		get_fork(ph, fork1);
		get_fork(ph, fork2);
		eat_and_release(ph, fork1, fork2);
		gettimeofday(&now, NULL);
		ph_sleep(ph);
		if (!ph->game->is_over)
			pri_mut(&(ph->game->print), "%d %d is thinking\n",
				time_ms(now, ph->game->start), ph->num);
	}
	return (0);
}

void	*ph(void *arg)
{
	t_ph	*ph;

	ph = (t_ph *)arg;
	pri_mut(&(ph->game->print), "philosopher %d started\n", ph->num);
	if (ph->num % 2)
		usleep(50);
	ph_life_cycle(ph);
	return (NULL);
}
