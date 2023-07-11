/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 02:02:02 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/11 16:50:35 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_node	coordinate_to_pixel(t_fdf *f, t_coordinate t, int color)
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
