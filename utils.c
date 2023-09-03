/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 09:21:15 by dgutak            #+#    #+#             */
/*   Updated: 2023/07/27 09:23:49 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f');
}

static int	count_dig(int n)
{
	int	i;

	i = 1;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n > 9)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	int	x;
	int	sign;

	x = 0;
	sign = 1;
	while (*str == ' ' || *str == '\v'
		|| *str == '\t' || *str == '\n' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			x = x * 10 + *str - '0';
		else
			break ;
		str++;
	}
	return (sign * x);
}

int	fill_map(char *str, t_data *data)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (str[i] && k < (data->rows * data->cols))
	{
		while (is_space(str[i]) == 1)
			i++;
		data->point[k].z = ft_atoi(str + i);
		i = i + count_dig(data->point[k].z);
		while (is_space(str[i]) == 0 && str[i])
			i++;
		data->point[k].x = k % data->cols;
		data->point[k].y = k / data->cols;
		k++;
	}
	return (0);
}

int	count_words(const char *str)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (!is_space(*str))
		{
			if (!in_word)
			{
				in_word = 1;
				count++;
			}
		}
		else
			in_word = 0;
		str++;
	}
	return (count);
}
