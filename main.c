/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:47:07 by dgutak            #+#    #+#             */
/*   Updated: 2023/07/23 20:56:52 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"

void	ft_new_image(t_data *data, int width, int height) {
	data->img->reference = mlx_new_image(data->mlx_ptr, width, height);
	data->img->width = width;
	data->img->height = height;
	data->img->pixels = (int*)mlx_get_data_addr(data->img->reference, &data->img->bits_per_pixel, &data->img->line_size, &data->img->endian);
	data->img->bits_per_pixel /= 8;
}
/* 
void 3dshift(data);

 */

t_bresenham	bresenham_init(t_point p1, t_point p2)
{
	t_bresenham	bres;

	bres.dx = abs(p2.x - p1.x);
	bres.dy = abs(p2.y - p1.y);
	bres.sx = -1;
	bres.sy = -1;
	if (p1.x < p2.x)
		bres.sx = 1;
	if (p1.y < p2.y)
		bres.sy = 1;
	bres.err = bres.dx - bres.dy;
	return (bres);
}

void	bresenham(t_data *data, t_point p1, t_point p2)
{
	t_bresenham	bres;

	bres = bresenham_init(p1, p2);
	while (p1.x != p2.x || p1.y != p2.y)
	{
		data->img->pixels[(data->img->width * p1.y) + p1.x] = data->color;
		bres.e2 = 2 * bres.err;
		if (bres.e2 > -bres.dy)
		{
			bres.err -= bres.dy;
			p1.x += bres.sx;
		}
		if (bres.e2 < bres.dx)
		{
			bres.err += bres.dx;
			p1.y += bres.sy;
		}
	}
}
void draw_net(t_data *data) {
	int index = 0;
	int col = 0;
	int row = 0;
	index = -1;
	col = 0;
	row = 0;
	while (++index < data->rows * data->cols) 
	{
		if (!(data->point[index].x < data->img->width && data->point[index+ 1].x < data->img->width
			&& data->point[index].y < data->img->height && data->point[index+ 1].y < data->img->height))
			continue ;
		if (col < data->cols - 1 && col < data->img->width) {
			bresenham(data, data->point[index], data->point[index + 1]);
		}
		if (row < data->rows - 1 && row < data->img->height) {
			bresenham(data, data->point[index], data->point[index + data->cols]);
		}
		if (++col == data->cols) {
			col = 0;
			row++;
		}
	}
}
void  draw_image(t_data *data)
{
	ft_new_image(data,800,600);
	draw_net(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->reference, 0,0);
	mlx_destroy_image(data->mlx_ptr, data->img->reference);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 30, data->color, "Color: 0x00");
}
int key_hook(int keycode, t_data *data)
{
	if (keycode == 0xFF1B)
	{
		mlx_destroy_window(data->mlx_ptr,data->win_ptr);
		free(data->img);
		exit(0);
	} // Escape key (keycode for ESC)
		
	else if (keycode == 0x0031) // Key "1" (keycode for 1) - Start movement
	{
		data->key_held = 1;
	}
	else if (keycode == 0x0032) // Key "2" (keycode for 2) - Stop movement
	{
		data->color = 0x00FFFF;
	}
	else if (keycode == 0x0033) // Key "3" (keycode for 3) - Change color to blue
	{
		data->color = 0x0000FF; // Blue
		
	}
	else if (keycode == 0x0034) // Key "3" (keycode for 3) - Change color to blue
	{
		data->color = 0xFFFF00; // Blue
		
	}
	
	draw_image(data);
	return (0);
}
int key_hook_release(int keycode, t_data *data)
{
if (keycode == 0x0031) // Key "1" (keycode for 1) - Start movement
	{
		data->key_held = 0;
	}
return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
	{
		data.img = (t_image *)malloc(sizeof(t_image));
		if (data.img == NULL)
			return (1);
		ft_map_create(argv[1], &data);
		data.color = 0xFF0000;
		data.mlx_ptr = mlx_init();
		data.win_ptr = mlx_new_window(data.mlx_ptr, 800, 600,
				"Minilibx Square");
		data.key_held = 0;
		mlx_hook(data.win_ptr, 2, 1L << 0, key_hook, &data);
		mlx_hook(data.win_ptr, 3, 1L << 1, key_hook_release, &data);
		draw_image(&data);
		mlx_loop(data.mlx_ptr);
	}
	return (0);
}
