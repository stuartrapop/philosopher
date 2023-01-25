/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:57:50 by srapopor          #+#    #+#             */
/*   Updated: 2023/01/25 09:36:44 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ph_eat(t_ph *ph)
{
	struct timeval	now;
	int				fork1;
	int				fork2;

	if (ph->number == 0)
		fork1 = ph->game->number_phs;
	else
		fork1 = ph->number - 1;
	fork2 = ph->number;
	while (1)
	{
		pthread_mutex_lock(&(ph->phs[fork1].fork));
		gettimeofday(&now, NULL);
		pri_mut(&(ph->game->print), "%d %d has taken a fork\n", time_ms(now, ph->game->time), ph->number);
		pthread_mutex_lock(&(ph->phs[fork2].fork));
		gettimeofday(&now, NULL);
		pri_mut(&(ph->game->print), "%d %d has taken a fork\n", time_ms(now, ph->game->time), ph->number);
		gettimeofday(&now, NULL);
		ph->eating = time_ms(now, ph->game->time);
		pri_mut(&(ph->game->print), "%d %d is eating\n", ph->eating, ph->number);
		while ((time_ms(now, ph->game->time) - ph->eating) < ph->game->t_eat)
			gettimeofday(&now, NULL);
		pthread_mutex_unlock(&(ph->phs[fork1].fork));
		pthread_mutex_unlock(&(ph->phs[fork2].fork));
		gettimeofday(&now, NULL);
		ph->sleeping = time_ms(now, ph->game->time);
		pri_mut(&(ph->game->print), "%d %d is sleeping\n", ph->sleeping, ph->number);
		while ((time_ms(now, ph->game->time) - ph->sleeping) < ph->game->t_sleep)
			gettimeofday(&now, NULL);
		pri_mut(&(ph->game->print), "%d %d is thinking\n", time_ms(now, ph->game->time), ph->number);
	}
	return (0);
}

void	*ph(void *arg)
{
	t_ph	*ph;

	ph = (t_ph *)arg;
	pri_mut(&(ph->game->print), "ph %d started\n", ph->number);
	if (ph->number % 2)
		usleep(50);
	ph_eat(ph);
	return ((void *)&(ph->number));
}

void	*game_monitor(void *arg)
{
	t_ph			**phs;
	struct timeval	now;
	int				index;
	long			ts;

	phs = (t_ph **)arg;
	index = 0;
	while (1)
	{
		gettimeofday(&now, NULL);
		ts = time_ms(now, phs[0]->game->time);
		index = 0;
		while (index < phs[0]->game->number_phs)
		{
			usleep(20);
			if ((ts - phs[index]->eating) > phs[0]->game->t_die)
			{
				pri_mut(&(phs[0]->game->print), "%d %d has died\n", ts, index);
				return ((void *)"I am done");
			}
			index++;
		}
	}
	return ((void *) "I am done");
}

int	ft_init_phs(t_ph *phs, t_game *game)
{
	int		index;
	void	*res;

	index = 0;
	pri_mut(&game->print, "number of philosophers %d \n", game->number_phs);
	while (index < game->number_phs)
	{
		usleep(20);
		phs[index].number = index;
		phs[index].eating = 0;
		phs[index].game = game;
		phs[index].phs = phs;
		pthread_mutex_init(&(phs[index].fork), NULL);
		pthread_create(&(phs[index].thread),
			NULL, ph, &(phs[index]));
		index++;
	}
	pthread_create(&(game->monitor_thread), \
		NULL, game_monitor, &(phs));
	pthread_join(game->monitor_thread, &res);
	pri_mut(&game->print, "\nmonitor: %s\n", (char *) res);
	index = 0;
	while (index < game->number_phs)
	{
		pthread_detach(phs[index].thread);
		pri_mut(&game->print, "detached %d\n", index);
		index++;
	}
	return (0);
}

int	treat_args(int argc, char *argv[], t_game *game, \
	t_ph *phs)
{
	game->number_phs = ft_atoi(argv[1]);
	game->t_die = ft_atoi(argv[2]);
	game->t_eat = ft_atoi(argv[3]);
	game->t_sleep = ft_atoi(argv[4]);
	gettimeofday(&game->time, NULL);
	pthread_mutex_init(&(game->print), NULL);
	if (argc == 6)
		game->num_eat = ft_atoi(argv[5]);
	phs = malloc(sizeof(t_ph) * \
		(game->number_phs));
	usleep(10);
	ft_init_phs(phs, game);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_game	game;
	t_ph	*phs;

	if (argc < 5 | argc > 6)
		return (2);
	phs = NULL;
	treat_args(argc, argv, &game, phs);
	return (0);
}
