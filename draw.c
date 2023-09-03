/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 08:40:32 by dgutak            #+#    #+#             */
/*   Updated: 2023/07/31 18:03:35 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_new_image(t_data *data, int width, int height)
{
	data->img->reference = mlx_new_image(data->mlx_ptr, width, height);
	data->img->width = width;
	data->img->height = height;
	data->img->pixels = (int *)mlx_get_data_addr(data->img->reference,
			&data->img->bits_per_pixel,
			&data->img->line_size, &data->img->endian);
	data->img->bits_per_pixel /= 8;
}

void	print_menu(t_data data)
{
	char	*menu;

	menu = "ARROWS: move";
	mlx_string_put(data.mlx_ptr, data.win_ptr, 10, 20, 0x03fcFF, menu);
	menu = "WS: rotation; AD: Z-scale; +, -: zoom";
	mlx_string_put(data.mlx_ptr, data.win_ptr, 10, 35, 0x03fcFF, menu);
	menu = "UO: z-rotation; IK: y-rotation; JL: x-rotation";
	mlx_string_put(data.mlx_ptr, data.win_ptr, 10, 50, 0x03fcFF, menu);
	menu = "R: reset image, ESC: exit";
	mlx_string_put(data.mlx_ptr, data.win_ptr, 10, 65, 0x03fcFF, menu);
}

void	bresenham(t_data *data, t_point p1, t_point p2)
{
	float	ex;
	float	ey;
	float	max;
	int		index;

	transformation(data, &p1);
	transformation(data, &p2);
	ex = p2.x - p1.x;
	ey = p2.y - p1.y;
	max = fmax(fabs(ex), fabs(ey));
	ey /= max;
	ex /= max;
	while ((int)(p1.x - p2.x) || (int)(p1.y - p2.y))
	{
		index = data->img->width * (int)p1.y + (int)p1.x;
		if (p1.y < data->img->height && index >= 0 && p1.y >= 0 && p1.x >= 0
			&& p1.x < data->img->width)
			data->img->pixels[index] = data->color;
		p1.x += ex;
		p1.y += ey;
	}
}

void	draw_net(t_data *data)
{
	int	index;
	int	col;
	int	row;

	index = -1;
	col = 0;
	row = 0;
	while (++index < data->rows * data->cols)
	{
		if (row < data->rows - 1)
			bresenham(data, data->point[index], data->point[index
				+ data->cols]);
		if (col < data->cols - 1)
			bresenham(data, data->point[index], data->point[index + 1]);
		if (++col == data->cols)
		{
			col = 0;
			row++;
		}
	}
}

void	draw_image(t_data *data)
{
	ft_new_image(data, 1000, 1000);
	draw_net(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->reference,
		0, 0);
	mlx_destroy_image(data->mlx_ptr, data->img->reference);
	print_menu(*data);
}
