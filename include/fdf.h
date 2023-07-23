/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:45:20 by dgutak            #+#    #+#             */
/*   Updated: 2023/07/23 18:51:47 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_image
{
	void	*reference;
	int		*pixels;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_size;
	int		endian;

}			t_image;
typedef struct s_bresenham
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
	int		x;
	int		y;
}			t_bresenham;
typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
}			t_point;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_point	*point;
	int		rows;
	int		cols;
	int		color;
	int		key_held;
	t_image	*img;
}			t_data;

void		ft_readmap(int fd, t_data *data);
void		ft_map_create(char *file, t_data *data);

#endif