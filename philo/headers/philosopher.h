/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:33:49 by srapopor          #+#    #+#             */
/*   Updated: 2023/01/26 15:56:33 by srapopor         ###   ########.fr       */
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

typedef struct s_game {
	int				number_phs;
	struct timeval	start;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				num_eat;
	pthread_t		monitor_thread;
	pthread_mutex_t	print;

}	t_game;

typedef struct s_ph {
	int					num;
	int					num_times_eaten;
	pthread_mutex_t		num_eat_mutex;
	int					eat;
	int					sleep;
	int					think;
	pthread_t			thread;
	pthread_mutex_t		fork;
	pthread_mutex_t		eat_mutex;
	int					stop_printing;
	t_game				*game;
	struct s_ph			*phs;

}	t_ph;

int		time_ms(struct timeval time_value, struct timeval time);
int		ft_strcmp(char *s1, char *s2);
int		ft_isdigit(char c);
int		ft_atoi(char *str);
void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_printf(const char *formatted_string, ...);
void	ft_putnum(int num);
void	pri_mut(pthread_mutex_t *mutex, const char *formatted_string, ...);
int		get_fork(t_ph *ph, int fork);
int		eat_and_release(t_ph *ph, int fork1, int fork2);
int		ph_sleep(t_ph *ph);
void	ph_life_cycle(t_ph *ph);
void	*ph(void *arg);
int		check_eating_time(t_ph *phs, int ph_number, int *pass_cycle_test);
void	set_stop_printing(t_ph *phs);

#endif