/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 02:02:02 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/14 19:56:35 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_node	new_pixel(t_fdf *fdf, int axis, int ordinate, int altitude)
{
	t_matrix	tmp;
	t_node		start;
	int			color;
	color = get_altitude_color(fdf->map, altitude);
	tmp = dup_coordinate(axis, ordinate, altitude, color);
	start = coordinate_to_pixel(fdf, tmp, color);
	return (start);
}

t_matrix	dup_coordinate(int axis, int ordinate, int altitude, int color)
{
	t_matrix	new_node;

	new_node.axis = axis;
	new_node.ordinate = ordinate;
	new_node.altitude = altitude;
	new_node.color = color;
	return (new_node);
}

t_node	coordinate_to_pixel(t_fdf *f, t_matrix t, int color)
{
	t_node		new_node;
	int			zoom;
	int			x;
	int			y;

	zoom = f->camera->zoom;
	x = t.ordinate * zoom;
	y = t.axis * zoom;
	x -= (f->map->width * zoom) / 2;
	y -= (f->map->height * zoom) / 2;
	new_node.x = x;
	new_node.y = y;
	new_node.z = t.altitude * zoom / f->camera->z_divisor;
	new_node.color = color;
	rotate_x(&new_node.y, &new_node.z, f->camera->alpha);
	rotate_y(&new_node.x, &new_node.z, f->camera->beta);
	rotate_z(&new_node.x, &new_node.y, f->camera->gamma);
	if (f->camera->projection == ISOMETRIC)
		iso(&new_node.x, &new_node.y, new_node.z);
	new_node.x += f->camera->x_offset + WIDTH / 2 + f->camera->zoom / 2;
	new_node.y += f->camera->y_offset + HEIGHT / 2 + f->camera->zoom / 2;
	new_node.altitude = t.altitude;
	return (new_node);
}

int	get_altitude_color(t_map *map, int z)
{
	int		color;
	double	percentage;

	percentage = (double)(z - map->z_min) / map->z_range;
	if (percentage < 0.2)
		color = COLOR_DISCO;
	else if (percentage < 0.4)
		color = COLOR_BRICK_RED;
	else if (percentage < 0.6)
		color = COLOR_FLAMINGO;
	else if (percentage < 0.8)
		color = COLOR_JAFFA;
	else
		color = COLOR_SAFFRON;
	return (color);
}
