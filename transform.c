/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 09:56:25 by dgutak            #+#    #+#             */
/*   Updated: 2023/09/21 15:14:39 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotatex(t_point *point, t_data *data)
{
	float	cos_angle;
	float	sin_angle;
	float	new_y;
	float	new_z;

	point->x *= data->zoom;
	point->y *= data->zoom;
	point->z *= data->z_value;
	cos_angle = cos(data->xangle);
	sin_angle = sin(data->xangle);
	new_y = point->y * cos_angle - point->z * sin_angle;
	new_z = point->y * sin_angle + point->z * cos_angle;
	point->y = new_y;
	point->z = new_z;
}

void	rotatey(t_point *point, t_data *data)
{
	float	cos_angle;
	float	sin_angle;
	float	new_x;
	float	new_z;

	cos_angle = cos(data->yangle);
	sin_angle = sin(data->yangle);
	new_x = point->x * cos_angle + point->z * sin_angle;
	new_z = -point->x * sin_angle + point->z * cos_angle;
	point->x = new_x;
	point->z = new_z;
}

void	rotatez(t_point *point, t_data *data)
{
	float	cos_angle;
	float	sin_angle;
	float	new_x;
	float	new_y;

	cos_angle = cos(data->zangle);
	sin_angle = sin(data->zangle);
	new_x = point->x * cos_angle - point->y * sin_angle;
	new_y = point->x * sin_angle + point->y * cos_angle;
	point->x = new_x;
	point->y = new_y;
}

void	transformation(t_data *data, t_point *p1, t_point *p2)
{
	if (p1->z > 1 || p2->z > 1)
		data->color = fmin(0xf826af + (fmax(p1->z, p2->z) - 1) * 400, 0xFFFFFF);
	else
		data->color = 0x9afd6f;
	rotatex(p1, data);
	rotatey(p1, data);
	rotatez(p1, data);
	rotatex(p2, data);
	rotatey(p2, data);
	rotatez(p2, data);
	if (data->mode == 0)
	{
		p1->x = (p1->x - p1->y) * cos(data->angle);
		p1->y = (p1->x + p1->y) * sin(data->angle) - p1->z;
		p2->x = (p2->x - p2->y) * cos(data->angle);
		p2->y = (p2->x + p2->y) * sin(data->angle) - p2->z;
	}
	p1->x += data->mover - data->movel;
	p1->y += data->moved - data->moveu;
	p2->x += data->mover - data->movel;
	p2->y += data->moved - data->moveu;
}
