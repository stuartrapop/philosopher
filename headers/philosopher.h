/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:33:49 by srapopor          #+#    #+#             */
/*   Updated: 2023/01/25 09:35:55 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

enum e_state{eating, thinking, sleeping};

typedef struct s_game {
	int				current_eating;
	int				number_phs;
	struct timeval	time;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				num_eat;
	pthread_t		monitor_thread;
	pthread_mutex_t	print;
	pthread_mutex_t	monitor;

}	t_game;

typedef struct s_ph {
	enum e_state			state;
	int						number;
	int						eating;
	int						sleeping;
	int						thinking;
	pthread_t				thread;
	pthread_mutex_t			fork;
	t_game					*game;
	struct s_ph	*phs;

}	t_ph;

int		time_ms(struct timeval time_value, struct timeval time);
int		ft_strcmp(char *s1, char *s2);
int		ft_isdigit(char c);
int		ft_atoi(char *str);
void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_printf(const char *formatted_string, ...);
void	ft_putnum(int num);
void	pri_mut(pthread_mutex_t *mutex, \
					const char *formatted_string, ...);

#endif