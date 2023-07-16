/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw-image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 00:39:52 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 14:07:59 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_background(t_fdf *fdf)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(i < HEIGHT)
	{
		j = 0;
		while(j < WIDTH)
		{
			draw_pixel(fdf->canvas, j, i, BACKGROUND);
			j++;
		}
		i++;
	}
}

void	draw_image_new(t_fdf *fdf)
{
	int axis;

	axis = 0;
	draw_background(fdf);
	while(axis < fdf->map->height)
	{
		draw_each_row_new(fdf, axis);
		axis++;
	}

}

void	draw_each_row_new(t_fdf *fdf, int axis)
{
	t_node		start;
	t_node		end;
	int			ordinate;
	int			idx;

	ordinate = 0;
	while(ordinate < fdf->map->width)
	{
		idx = axis * fdf->map->width + ordinate;
		start = create_node(fdf, axis, ordinate, fdf->h_mtx[idx]);
		if (ordinate != fdf->map->width - 1)
			end = create_node(fdf, axis, ordinate + 1, fdf->h_mtx[idx + 1]);

		if (ordinate != fdf->map->width - 1)
			draw_line(start, end, fdf->canvas);
		
		if (axis != 0)
		{
			start = create_node(fdf, axis, ordinate, fdf->h_mtx[idx]);
			idx = (axis - 1) * fdf->map->width + ordinate;
			end = create_node(fdf, axis - 1, ordinate, fdf->h_mtx[idx]);
			draw_line(start, end, fdf->canvas);
		}
		ordinate++;
	}
}

