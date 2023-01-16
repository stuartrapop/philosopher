/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:57:50 by srapopor          #+#    #+#             */
/*   Updated: 2023/01/16 11:35:16 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	philosopher_eat(t_philosopher *philosopher)
{
	struct timeval	now;
	int				fork1;
	int				fork2;
	int				start_ms;

	if (philosopher->number == 0)
		fork1 = philosopher->game->number_philosophers;
	else
		fork1 = philosopher->number - 1;
	fork2 = philosopher->number;
	while (1)
	{
		pthread_mutex_lock(&(philosopher->philosophers[fork1].fork));
		pthread_mutex_lock(&(philosopher->philosophers[fork2].fork));
		gettimeofday(&now, NULL);
		start_ms = time_ms(now);
		philosopher->start_eating = start_ms;
		usleep(philosopher->game->time_to_eat * 1000);
		pthread_mutex_unlock(&(philosopher->philosophers[fork1].fork));
		pthread_mutex_unlock(&(philosopher->philosophers[fork2].fork));
		usleep(philosopher->game->time_to_sleep * 1000);
	}
	return (0);
}

void	*start_philosopher(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	printf("philosopher %d started\n", philosopher->number);

	return ((void *) &(philosopher->number));
}

int	ft_init_philosophers(t_philosopher *philosophers, t_game *game)
{
	int		index;
	void	*res;

	index = 0;
	printf(" number of philosophers %d\n", game->number_philosophers);
	while (index < game->number_philosophers)
	{
		philosophers[index].state = thinking;
		philosophers[index].number = index;
		philosophers[index].start_eating = 0;
		philosophers[index].start_sleeping = 0;
		philosophers[index].start_thinking = 0;
		philosophers[index].game = game;
		philosophers[index].philosophers = philosophers;
		pthread_mutex_init(&(philosophers[index].fork), NULL);
		pthread_create(&(philosophers[index].thread),
			NULL, start_philosopher, &(philosophers[index]));
		usleep(300);
		index++;
	}
	index = 0;
	while (index < game->number_philosophers)
	{
		pthread_join(philosophers[index].thread, &res);
		index++;
	}
	return (0);
}

int	treat_args(int argc, char *argv[], t_game *game, \
	t_philosopher *philosophers)
{
	game->number_philosophers = ft_atoi(argv[1]);
	game->time_to_die = ft_atoi(argv[2]);
	game->time_to_eat = ft_atoi(argv[3]);
	game->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		game->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	philosophers = malloc(sizeof(t_philosopher) * \
		(game->number_philosophers));
	ft_init_philosophers(philosophers, game);
	return (0);
}

int	main(int argc, char *argv[])
{
	struct timeval	now;
	t_game			game;
	t_philosopher	*philosophers;

	if (argc < 5 | argc > 6)
		return (2);
	philosophers = NULL;
	treat_args(argc, argv, &game, philosophers);
	gettimeofday(&now, NULL);
	printf ("time = %d\n", time_ms(now));



	printf("hello world\n");
	return (0);
}