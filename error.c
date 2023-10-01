/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 18:21:48 by dgutak            #+#    #+#             */
/*   Updated: 2023/09/25 11:45:01 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	esc(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	ft_printf(" Program run successfully\n");
	free(data->img);
	free(data->mlx_ptr);
	free(data->point);
	exit(0);
}

int	eror(t_data *data, int code, void *fred1, void *fred2)
{
	if (code != 0)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		if (data->img != NULL)
			free(data->img);
		free(data->mlx_ptr);
	}
	if (fred1 != NULL)
		free(fred1);
	if (fred2 != 0)
		free(fred2);
	ft_printf(" Something went wrong:P\n");
	exit(0);
}
