/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:01:34 by srapopor          #+#    #+#             */
/*   Updated: 2023/01/10 14:08:25 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	time_ms(struct timeval time_value)
{
	return ((int)((time_value.tv_sec) * 1000 + (time_value.tv_usec) / 1000));
}

int	ft_strcmp(char *s1, char *s2)
{
	int	index;

	index = 0;
	while (s1[index] != '\0')
	{
		if (s1[index] != s2[index])
			return (s1[index] - s2[index]);
		index++;
	}
	return (s1[index] - s2[index]);
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '0');
}

int	ft_atoi(char *str)
{
	int	sign;
	int	number;
	int	index;

	if (ft_strcmp(str, "-2147483648") == 0)
		return (-2147483648);
	number = 0;
	sign = 1;
	index = 0;
	while (str[index] == ' ')
		index++;
	if (str[index] == '+' || str[index] == '-')
	{
		if (str[index] == '-')
			sign = -1;
		index++;
	}
	while (str[index] != '\0')
	{
		number = number * 10 + (str[index] - '0');
		index++;
	}
	return (sign * number);
}