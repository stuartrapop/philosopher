/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:57:50 by srapopor          #+#    #+#             */
/*   Updated: 2023/01/10 16:36:09 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	philosopher_eat(t_philosopher *philosopher)
{
	if (philosopher->number == 0 && philosopher->game->number_philosophers == 1)
		return (1);
	else
	{
		if (philosopher->number == 0)
			pthread_mutex_lock(&(philosopher->philosophers[0]));
			pthread_mutex_lock(&(philosopher->philosophers[philosopher->game->number_philosophers]));
			

	}
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
		philosophers[index].fork_in_use = 0;
		philosophers[index].game = game;
		philosophers[index].philosophers = philosophers;
		pthread_mutex_init(&(philosophers[index].mutex), NULL);
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