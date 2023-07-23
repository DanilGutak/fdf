/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:04:11 by dgutak            #+#    #+#             */
/*   Updated: 2023/07/23 20:34:47 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"
#include "include/get_next_line.h"

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
		data->point[k].x = k % data->cols*2;
		data->point[k].y = (data->rows - 1 - k / data->cols)*2;
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

void	ft_map_create(char *file, t_data *data)
{
	int	fd;

	fd = open(file, 0);
	if (fd == -1)
		return ;
	ft_readmap(fd, data);
	close(fd);
}

void	ft_readmap(int fd, t_data *data)
{
	char	*temp;
	char	*buf;

	data->rows = 0;
	buf = ft_calloc(1, 1);
	if (!buf)
		return ;
	temp = get_next_line(fd);
	if (!temp)
		return ;
	data->cols = count_words(temp);
	while (temp && ++data->rows)
	{
		if (data->cols != count_words(temp) || data->cols == 0)
			return ;
		buf = ft_strjoin(buf, temp);
		temp = get_next_line(fd);
	}
	data->point = calloc(data->rows * data->cols, sizeof(t_point));
	if (!data->point)
		return ;
	fill_map(buf, data);
	return ;
}
