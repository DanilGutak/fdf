/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:04:11 by dgutak            #+#    #+#             */
/*   Updated: 2023/07/30 14:55:15 by dgutak           ###   ########.fr       */
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

void	ft_readmap(int fd, t_data *data)
{
	char	*temp;
	char	*buf;

	buf = ft_calloc(1, 1);
	if (!buf)
		eror(data, 1, NULL, NULL);
	temp = get_next_line(fd);
	if (temp == NULL)
		eror(data, 1, buf, NULL);
	data->cols = count_words(temp);
	while (temp && ++data->rows)
	{
		if (data->cols != count_words(temp) || data->cols == 0)
			eror(data, 1, buf, temp);
		buf = ft_strjoin(buf, temp);
		free(temp);
		temp = get_next_line(fd);
	}
	free(temp);
	data->point = calloc(data->rows * data->cols, sizeof(t_point));
	if (!data->point)
		eror(data, 1, buf, NULL);
	fill_map(buf, data);
	free(buf);
}
