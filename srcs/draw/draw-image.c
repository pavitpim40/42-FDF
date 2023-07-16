/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw-image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 00:39:52 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 12:35:13 by ppimchan         ###   ########.fr       */
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
			draw_pixel(fdf->canvas, j, i, BACKGROUND);
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
		start = create_node(fdf, axis, ordinate, fdf->h_mtx[idx]);
		// printf("start: %d, %d\n", start.x, start.y);
		

		if (ordinate != fdf->map->width - 1)
			end = create_node(fdf, axis, ordinate + 1, fdf->h_mtx[idx + 1]);
		// else
		// 	end = create_node(fdf, axis, ordinate, fdf->h_mtx[idx]);
		if (ordinate != fdf->map->width - 1)
		{
			draw_line(start, end, fdf->canvas);
			count++;
		}
			// draw_line(start, end, fdf->canvas);
		if (axis != 0)
		{
			start = create_node(fdf, axis, ordinate, fdf->h_mtx[idx]);
			idx = (axis - 1) * fdf->map->width + ordinate;
			end = create_node(fdf, axis - 1, ordinate, fdf->h_mtx[idx]);
			// printf("draw vertical\n");
			// printf("start (x, y): %d, %d\n", start.x, start.y);
			// printf("end (x, y): %d, %d\n\n", end.x, end.y);
			draw_line(start, end, fdf->canvas);
			count++;
		}
		ordinate++;
	}
	
}

