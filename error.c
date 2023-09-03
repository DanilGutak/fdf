/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 18:21:48 by dgutak            #+#    #+#             */
/*   Updated: 2023/07/30 14:58:02 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* void error_ret(char *str)
{
	
} */

int	esc(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	ft_printf(" Program run successfully\n");
	free(data->img);
	exit(0);
}

int	eror(t_data *data, int code, void *fred1, void *fred2)
{
	if (code != 0)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		
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
