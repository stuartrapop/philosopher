/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:05:04 by srapopor          #+#    #+#             */
/*   Updated: 2023/01/26 08:51:40 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		ft_putchar(str[index]);
		index++;
	}
}

static void	ft_print_arg(const char *format_string, va_list *list)
{
	char	format;

	format = format_string[1];
	if (format == 's')
		ft_putstr(va_arg(*list, char *));
	else if (format == 'c')
		ft_putchar(va_arg(*list, int));
	else if (format == 'i' || format == 'd')
		ft_putnum(va_arg(*list, int));
	else if (format == '%')
		write(1, "%", 1);
}

void	ft_printf(const char *formatted_string, ...)
{
	va_list	list;
	int		index;

	va_start(list, formatted_string);
	index = 0;
	while (formatted_string[index] != '\0')
	{
		if (formatted_string[index] == '%')
		{
			ft_print_arg((const char *)&formatted_string[index], &list);
			index++;
		}
		else
			ft_putchar(formatted_string[index]);
		index++;
	}
	va_end(list);
}

void	pri_mut(pthread_mutex_t *mutex, \
	const char *formatted_string, ...)
{
	va_list	list;
	int		index;

	pthread_mutex_lock(mutex);
	va_start(list, formatted_string);
	index = 0;
	while (formatted_string[index] != '\0')
	{
		if (formatted_string[index] == '%')
		{
			ft_print_arg((const char *)&formatted_string[index], &list);
			index++;
		}
		else
			ft_putchar(formatted_string[index]);
		index++;
	}
	va_end(list);
	pthread_mutex_unlock(mutex);
	usleep(20);
}
