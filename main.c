/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:47:07 by dgutak            #+#    #+#             */
/*   Updated: 2023/09/25 11:45:26 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"

void	data_init(t_data *data)
{
	data->zoom = fmax(25 - data->cols / 10, 1.5);
	data->z_value = 1;
	data->angle = 0.8;
	data->xangle = -0.3;
	data->yangle = 0;
	data->zangle = 0;
	data->moved = 200;
	data->movel = 0;
	data->mover = 600;
	data->moveu = 0;
	data->mode = 0;
}

void	key_hook2(int keycode, t_data *data)
{
	if (keycode == 0x0064)
		data->z_value *= 1.05;
	else if (keycode == 0x0061 && (data->z_value > 0.05 || data->z_value
			< -0.05))
		data->z_value /= 1.05;
	else if (keycode == 0x006A)
		data->xangle += 0.05;
	else if (keycode == 0x006C)
		data->xangle -= 0.05;
	else if (keycode == 0x0069)
		data->yangle += 0.05;
	else if (keycode == 0x006B)
		data->yangle -= 0.05;
	else if (keycode == 0x0075)
		data->zangle += 0.1;
	else if (keycode == 0x006F && data->z_value > 0.1)
		data->zangle -= 0.1;
	else if (keycode == 0x0072)
		data_init(data);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 0xFF1B)
		esc(data);
	else if (keycode == 0xFFAD && data->zoom > 0)
		data->zoom -= 0.5;
	else if (keycode == 0xFFAB && data->zoom < 40)
		data->zoom += 1;
	else if (keycode == 0xFF53)
		data->mover += 10;
	else if (keycode == 0xFF51)
		data->movel += 10;
	else if (keycode == 0xFF52)
		data->moveu += 10;
	else if (keycode == 0xFF54)
		data->moved += 10;
	else if (keycode == 0x0031)
	{
		data->mode = 1 - data->mode;
		data->xangle = -0.3 - data->xangle;
	}
	else
		key_hook2(keycode, data);
	return (draw_image(data), 0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (argc == 2)
	{
		data.img = (t_image *)malloc(sizeof(t_image));
		if (data.img == NULL)
			eror(&data, 0, NULL, NULL);
		data.rows = 0;
		data.mlx_ptr = mlx_init();
		if (data.mlx_ptr == NULL)
			eror(&data, 0, NULL, NULL);
		data.win_ptr = mlx_new_window(data.mlx_ptr, 1200, 800, "FDF");
		if (data.win_ptr == NULL)
			eror(&data, 0, NULL, NULL);
		ft_map_create(argv[1], &data);
		data_init(&data);
		mlx_hook(data.win_ptr, 2, 1L << 0, key_hook, &data);
		mlx_hook(data.win_ptr, 17, 0L, esc, &data);
		draw_image(&data);
		mlx_loop(data.mlx_ptr);
	}
	else
		return (ft_printf("Something went wrong:P\n(number of args)\n"), 1);
	return (0);
}
