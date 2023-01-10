/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:33:49 by srapopor          #+#    #+#             */
/*   Updated: 2023/01/10 17:15:03 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

enum e_state{eating, thinking, sleeping};

typedef struct s_game {
	int				current_eating;
	int				number_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;

}	t_game;

typedef struct s_philosopher {
	enum e_state			state;
	int						number;
	int						start_eating;
	int						start_sleeping;
	int						start_thinking;
	pthread_t				thread;
	pthread_mutex_t			fork;
	t_game					*game;
	struct s_philosopher	*philosophers;

}	t_philosopher;

int		time_ms(struct timeval time_value);
int		ft_strcmp(char *s1, char *s2);
int		ft_isdigit(char c);
int		ft_atoi(char *str);
void	ft_putchar(char c);
void	ft_putstr(char *str);

#endif