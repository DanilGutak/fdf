/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:04:11 by dgutak            #+#    #+#             */
/*   Updated: 2023/09/25 11:44:46 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"

void	ft_map_create(char *file, t_data *data)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		eror(data, 1, NULL, NULL);
	ft_readmap(fd, data);
	close(fd);
}

void	checkfile(char *buf, t_data *data, int fd)
{
	int		counter;
	int		in_word;
	char	*temp;

	temp = buf;
	while (*buf)
	{
		in_word = 0;
		counter = 0;
		while (*buf && *buf != '\n')
		{
			if (!is_space(*buf++))
			{
				if (!in_word)
					counter++;
				in_word = 1;
			}
			else
				in_word = 0;
		}
		if (*buf++ == 0)
			return ;
		if (data->cols != counter || data->cols == 0)
			(close(fd), eror(data, 1, temp, NULL));
	}
}

int	ft_readmap(int fd, t_data *data)
{
	char	*temp;
	char	*buf;

	buf = ft_calloc(1, 1);
	if (!buf)
		return (close(fd), eror(data, 1, NULL, NULL), 1);
	temp = get_next_line(fd);
	if (temp == NULL)
		return (close(fd), eror(data, 1, buf, NULL), 1);
	data->cols = count_words(temp);
	while (temp && *temp != 0 && ++data->rows)
	{
		buf = ft_strjoin(buf, temp);
		free(temp);
		temp = get_next_line(fd);
		if (temp == NULL || buf == NULL)
			return (close(fd), eror(data, 1, buf, temp), 1);
	}
	free(temp);
	checkfile(buf, data, fd);
	data->point = calloc(data->rows * data->cols, sizeof(t_point));
	if (!data->point)
		return (close(fd), eror(data, 1, buf, NULL), 1);
	fill_map(buf, data);
	return (free(buf), 1);
}
