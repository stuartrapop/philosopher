/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:28:03 by srapopor          #+#    #+#             */
/*   Updated: 2023/01/26 15:37:14 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	get_fork(t_ph *ph, int fork)
{
	struct timeval	now;

	pthread_mutex_lock(&(ph->phs[fork].fork));
	gettimeofday(&now, NULL);
	pthread_mutex_lock(&(ph->eat_mutex));
	if (!ph->stop_printing)
		pri_mut(&(ph->game->print), "%d %d has taken a fork\n", \
			time_ms(now, ph->game->start), ph->num + 1);
	pthread_mutex_unlock(&(ph->eat_mutex));
	usleep(25);
	return (0);
}

int	eat_and_release(t_ph *ph, int fork1, int fork2)
{
	struct timeval	now;
	struct timeval	start;
	int				eat_time;

	get_fork(ph, fork1);
	get_fork(ph, fork2);
	pthread_mutex_lock(&ph->eat_mutex);
	gettimeofday(&now, NULL);
	start = ph->game->start;
	ph->eat = time_ms(now, start);
	eat_time = ph->eat;
	ph->num_times_eaten++;
	pthread_mutex_unlock(&ph->eat_mutex);
	usleep(50);
	pthread_mutex_lock(&ph->eat_mutex);
	if (!ph->stop_printing)
		pri_mut(&(ph->game->print), "%d %d is eating\n", eat_time, ph->num + 1);
	pthread_mutex_unlock(&ph->eat_mutex);
	while ((time_ms(now, start) - eat_time) < ph->game->t_eat)
		gettimeofday(&now, NULL);
	pthread_mutex_unlock(&(ph->phs[fork1].fork));
	pthread_mutex_unlock(&(ph->phs[fork2].fork));
	usleep(200);
	return (0);
}

int	ph_sleep(t_ph *ph)
{
	struct timeval	now;
	struct timeval	start;

	gettimeofday(&now, NULL);
	start = ph->game->start;
	ph->sleep = time_ms(now, start);
	usleep(50);
	pthread_mutex_lock(&(ph->eat_mutex));
	if (!ph->stop_printing)
		pri_mut(&(ph->game->print), "%d %d is sleeping\n", \
			ph->sleep, ph->num + 1);
	pthread_mutex_unlock(&(ph->eat_mutex));
	while ((time_ms(now, start) - ph->sleep) < ph->game->t_sleep)
		gettimeofday(&now, NULL);
	return (0);
}

void	ph_life_cycle(t_ph *ph)
{
	struct timeval	now;
	int				fork1;
	int				fork2;
	struct timeval	start;

	usleep(3000);
	fork1 = ph->num;
	if (ph->num == 0)
		fork2 = ph->game->number_phs -1;
	else
		fork2 = ph->num - 1;
	if (ph->game->number_phs == 1)
		fork2 = fork1;
	while (1)
	{
		eat_and_release(ph, fork1, fork2);
		ph_sleep(ph);
		gettimeofday(&now, NULL);
		pthread_mutex_lock(&ph->eat_mutex);
		start = ph->game->start;
		if (!ph->stop_printing)
			pri_mut(&(ph->game->print), "%d %d is thinking\n", \
				time_ms(now, start), ph->num + 1);
		pthread_mutex_unlock(&ph->eat_mutex);
	}
}

void	*ph(void *arg)
{
	t_ph	*ph;

	ph = (t_ph *)arg;
	pri_mut(&(ph->game->print), "philosopher %d started\n", ph->num + 1);
	usleep(1000);
	if (ph->num % 2)
		usleep(500);
	ph_life_cycle(ph);
	return (NULL);
}
