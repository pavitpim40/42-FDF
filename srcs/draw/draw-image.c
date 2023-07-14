/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw-image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:57:52 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/14 19:18:47 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"



void	draw_image(t_fdf *fdf)
{
	t_matrix	*tv;
	int			*arr_height;
	int			*prev_height;
	t_matrix	*tmp;
	int			i;

	tv = (t_matrix *)malloc(sizeof(t_matrix));
	arr_height = malloc(sizeof(int) * fdf->map->width);
	prev_height = malloc(sizeof(int) * fdf->map->width);
	init_meta_data(tv, arr_height, prev_height);
	tmp = fdf->head;
	while (tv->axis < fdf->map->height)
	{
		// printf("axis: %d\n", tv->axis);
		// printf("fdf->map->height: %d\n", fdf->map->height);
		draw_each_row(fdf, tv, arr_height, prev_height);
		i = 0;
		while (i < fdf->map->width)
		{
			prev_height[i] = arr_height[i];
			i++;
		}
		tv->ordinate = 0;
		tv->axis += 1;
	}
	fdf->head = tmp;
}

void	draw_each_row(t_fdf *fdf, t_matrix *tv, int *arr_h, int *prev_arr_h)
{
	t_node		start;
	t_node		end;

	while (tv->ordinate < fdf->map->width && fdf->head)
	{
		arr_h[tv->ordinate] = fdf->head->z;
		start = new_pixel(fdf, tv->axis, tv->ordinate, fdf->head->z);
		if (fdf->head->next)
			fdf->head = fdf->head->next;
		
		if(tv->ordinate != fdf->map->width - 1)
			arr_h[tv->ordinate + 1] = fdf->head->z;
		// printf("debug\n");
		end = new_pixel(fdf, tv->axis, tv->ordinate + 1, fdf->head->z);
		if (tv->ordinate != fdf->map->width - 1) 
			draw_line(start, end, fdf->canvas);
		if (tv->axis != 0)
		{
			tv->altitude = prev_arr_h[tv->ordinate];
			end = new_pixel(fdf, tv->axis - 1, tv->ordinate, tv->altitude);
			draw_line(start, end, fdf->canvas);
		}
		tv->ordinate++;
	}
}

void	free_meta_data(t_matrix *tv, int *arr_h, int *prev_h)
{
	if (tv)
		free(tv);
	if (arr_h)
		free(arr_h);
	if (prev_h)
		free(prev_h);
}

void	init_meta_data( t_matrix *tv, int *arr_h, int *prev_h)
{
	if (!tv || !arr_h || !prev_h)
	{
		free_meta_data(tv, arr_h, prev_h);
		return ;
	}
	tv->axis = 0;
	tv->ordinate = 0;
}

