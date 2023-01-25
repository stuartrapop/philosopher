/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:57:50 by srapopor          #+#    #+#             */
/*   Updated: 2023/01/25 19:22:50 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*game_monitor(void *arg)
{
	t_ph			*phs;
	int				index;
	int				pass_cycle_test;

	phs = (t_ph *)arg;
	index = 0;
	while (1)
	{
		pass_cycle_test = 1;
		index = 0;
		while (index < phs[0].game->number_phs)
		{
			if (check_eating_time(phs, index, &pass_cycle_test))
			{
				return ("Died");
			}
			index++;
		}
		if (pass_cycle_test && phs[0].game->num_eat != 0)
		{
			pthread_mutex_lock(&phs[0].game->monitor);
			phs[0].game->is_over = 1;
			pthread_mutex_unlock(&phs[0].game->monitor);
			usleep(200);
			pri_mut(&(phs[0].game->print), "Completed Cycles\n");
			return ("Completed Cycles");
		}
	}
	return ("Died");
}

int	ft_clean_game(t_ph *phs, t_game *game)
{
	int	index;

	index = 0;
	while (index < game->number_phs)
	{
		pthread_detach(phs[index].thread);
		pri_mut(&game->print, "detached %d\n", index);
		//pthread_mutex_destroy(&phs[index].fork);
		index++;
	}
	return (0);
}

int	ft_init_phs(t_ph *phs, t_game *game)
{
	int				index;
	void			*res;

	index = 0;
	pri_mut(&game->print, "number of philosophers %d \n", game->number_phs);
	while (index < game->number_phs)
	{
		pthread_mutex_init(&(phs[index].eat_mutex), NULL);
		phs[index].num = index;
		pthread_mutex_lock(&(game->monitor));
		phs[index].eat = 0;
		pthread_mutex_unlock(&(game->monitor));
		phs[index].game = game;
		phs[index].phs = phs;
		phs[index].num_times_eaten = 0;
		pthread_mutex_init(&(phs[index].fork), NULL);
		pthread_create(&(phs[index].thread), NULL, ph, &(phs[index]));
		index++;
		usleep(50);
	}
	usleep(2000);
	pthread_create(&game->monitor_thread, NULL, game_monitor, phs);
	pthread_join(game->monitor_thread, &res);
	ft_clean_game(phs, game);
	return (0);
}

int	treat_args(int argc, char *argv[], t_game *game, t_ph *phs)
{
	game->number_phs = ft_atoi(argv[1]);
	game->t_die = ft_atoi(argv[2]);
	game->t_eat = ft_atoi(argv[3]);
	game->t_sleep = ft_atoi(argv[4]);
	pthread_mutex_init(&game->monitor, NULL);

	pthread_mutex_lock(&(game->monitor));
	game->is_over = 0;
	pthread_mutex_unlock(&(game->monitor));
	gettimeofday(&game->start, NULL);
	pthread_mutex_init(&(game->print), NULL);
	if (argc == 6)
		game->num_eat = ft_atoi(argv[5]);
	else
		game->num_eat = 0;
	phs = malloc(sizeof(t_ph) * (game->number_phs));
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
