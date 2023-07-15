/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw-image-new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 00:39:52 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 05:05:07 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_image_new(t_fdf *fdf)
{
	int axis;
	// int ordinate;

	axis = 0;
	// ordinate = 0;
	int i = 0;
	int j = 0;
	// draw-background

	while(i < HEIGHT)
	{
		j = 0;
		while(j < WIDTH)
		{
			pixel_put(fdf->canvas, j, i, BACKGROUND);
			j++;
		}
		i++;
	}

	while(axis < fdf->map->height)
	{
		draw_each_row_new(fdf, axis);
		axis++;
		// printf("axis: %d\n", axis);
	}

}

void	draw_each_row_new(t_fdf *fdf, int axis)
{
	t_node		start;
	t_node		end;
	int		ordinate;
	int		idx;
	int count = 1;

	ordinate = 0;
	// printf(">>>>>>>>>>>>> DRAW AXIS: %d\n", axis);
	while(ordinate < fdf->map->width)
	{
		// printf("\naxis and ordinate: %d, %d\n", axis, ordinate);
		idx = axis * fdf->map->width + ordinate;
		start = get_pixel(fdf, axis, ordinate, fdf->h_mtx[idx]);
		// printf("start: %d, %d\n", start.x, start.y);
		

		if (ordinate != fdf->map->width - 1)
			end = get_pixel(fdf, axis, ordinate + 1, fdf->h_mtx[idx + 1]);
		// printf("draw horizontal\n");
		// printf("start (x, y): %d, %d\n", start.x, start.y);
		// printf("end (x, y): %d, %d\n\n", end.x, end.y);
		// printf("end: %d, %d\n", end.x, end.y);
		if (ordinate != fdf->map->width - 1)
		{
			// printf("draw horizontal\n");
			// printf("start->color: %x\n", start.color);
			// printf("end->color: %x\n", end.color);
			draw_line(start, end, fdf->canvas);
			count++;
		}
			// draw_line(start, end, fdf->canvas);
		if (axis != 0)
		{
			start = get_pixel(fdf, axis, ordinate, fdf->h_mtx[idx]);
			idx = (axis - 1) * fdf->map->width + ordinate;
			end = get_pixel(fdf, axis - 1, ordinate, fdf->h_mtx[idx]);
			// printf("draw vertical\n");
			// printf("start (x, y): %d, %d\n", start.x, start.y);
			// printf("end (x, y): %d, %d\n\n", end.x, end.y);
			draw_line(start, end, fdf->canvas);
			count++;
		}
		ordinate++;
	}
	
}

t_node	get_pixel(t_fdf *f, int axis, int ordinate, int altitude)
{

	t_node px;
	int			zoom;
	int			default_color;

	altitude = f->h_mtx[axis * f->map->width + ordinate];
	default_color = f->c_mtx[axis * f->map->width + ordinate];
	// printf("axis: %d, ordinate: %d\n", axis, ordinate);
	// printf("default_color: %x\n\n", default_color);
	if(default_color == -1)
		px.color = get_altitude_color(f->map, altitude);
	else 
		px.color = default_color;
	zoom = f->camera->zoom;
	px.x = ordinate * zoom;

	px.y = axis * zoom;
	px.x -= (f->map->width * zoom) / 2;
	px.y -= (f->map->height * zoom) / 2;
	px.z = altitude * zoom / f->camera->z_divisor;
	rotate_x(&px.y, &px.z, f->camera->alpha);
	rotate_y(&px.x, &px.z, f->camera->beta);
	rotate_z(&px.x, &px.y, f->camera->gamma);
	if (f->camera->projection == ISOMETRIC)
		iso(&px.x, &px.y, px.z);
	px.x += f->camera->x_offset + WIDTH / 2 + f->camera->zoom / 2;
	// printf("px.x: %d\n\n", px.x);
	px.y += f->camera->y_offset + HEIGHT / 2 + f->camera->zoom / 2;
	px.altitude = altitude;
	// printf("color: %d\n", px.color);

	return (px);

	return (px);
}