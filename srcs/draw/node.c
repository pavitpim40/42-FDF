/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:27:46 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/19 15:07:06 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_node	create_node(t_fdf *f, int axis, int ordinate, int altitude)
{
	t_node		px;
	int			zoom;
	int			default_color;

	altitude = f->h_mtx[axis * f->map->width + ordinate];
	default_color = f->c_mtx[axis * f->map->width + ordinate];
	if (default_color == -1)
		px.color = get_altitude_color(f->map, altitude);
	else
		px.color = default_color;
	zoom = f->camera->zoom;
	px.x = ordinate * zoom;
	px.y = axis * zoom;
	px.z = altitude * zoom / f->camera->z_divisor;
	px.x -= (f->map->width * zoom) / 2;
	px.y -= (f->map->height * zoom) / 2;
	rotate_x(&px.y, &px.z, f->camera->alpha);
	rotate_y(&px.x, &px.z, f->camera->beta);
	rotate_z(&px.x, &px.y, f->camera->gamma);
	if (f->camera->projection == ISOMETRIC)
		iso(&px.x, &px.y, px.z);
	px.x += f->camera->x_offset + WIDTH / 2 + f->camera->zoom / 2;
	px.y += f->camera->y_offset + HEIGHT / 2 + f->camera->zoom / 2;
	px.altitude = altitude;
	return (px);
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
