/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student->42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:57:52 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/03 23:41:00 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** my draw image strategy
** - draw from left to right each row
** - draw only horizontal line for first row
** - draw horizontal line with vertical line to previous for for the rest 
**   while traverse left to right
*/

void draw_image (t_fdf *fdf)
{
	t_map *map = fdf->map;
	t_coordinate *head = fdf->head;
	t_canvas *canvas = fdf->canvas;
	int axis = 0;
	int ordinate = 0;
	int arr_height[map->width];
	int prev_height[map->width];
	int color;
	while (axis < map->height)
	{
		while (ordinate < map->width  && head)
		{	
			color = get_altitude_color(map, head->z);
			t_node start = create_project_node(axis,ordinate,head->z,color,map);
			arr_height[ordinate] = head->z;

			// Draw horizontal line - end
			if (head->next)
				head = head->next;
			arr_height[ordinate + 1] = head->z;
			color = get_altitude_color(map, head->z);
			t_node end = create_project_node(axis,ordinate+1,head->z,color,map);
			arr_height[ordinate + 1] = head->z;
			if(ordinate != map->width - 1) 
					draw_line(start, end, canvas);
			
					
			// Draw vertical line - BACKWARD
			if (axis != 0)
			{
				int altitude = prev_height[ordinate];
				color = get_altitude_color(map, altitude);
				end = create_project_node(axis-1,ordinate,altitude,color,map);
				draw_line(start, end, canvas);
				}
			ordinate++;
		}
		int i = 0;
		while (i < map->width)
		{
			prev_height[i] = arr_height[i];
			i++;
		}
		ordinate = 0;
		axis++;
	}
}
