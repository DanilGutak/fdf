/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:45:20 by dgutak            #+#    #+#             */
/*   Updated: 2023/09/25 11:45:05 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdlib.h>

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

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	int		color;
}			t_point;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_point	*point;
	double	angle;
	double	zangle;
	double	xangle;
	double	yangle;
	int		mode;
	float	zoom;
	float	z_value;
	int		rows;
	int		cols;
	int		color;
	int		moved;
	int		movel;
	int		mover;
	int		moveu;
	t_image	*img;
}			t_data;

int			ft_readmap(int fd, t_data *data);
void		draw_image(t_data *data);
int			eror(t_data *data, int code, void *fred1, void *fred2);
void		ft_map_create(char *file, t_data *data);
int			count_words(const char *str);
int			fill_map(char *str, t_data *data);
int			ft_atoi(const char *str);
void		transformation(t_data *data, t_point *p1, t_point *p2);
int			esc(t_data *data);
int			is_space(char c);
#endif