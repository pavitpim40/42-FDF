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
	t_coordinate tv; // tv = traverse

	tv.axis = 0;
	tv.ordinate = 0;
	int arr_height[map->width];
	int prev_height[map->width];
	int color;
	while (tv.axis < map->height)
	{
		while (tv.ordinate < map->width  && head)
		{	
			color = get_altitude_color(map, head->z);
			tv.altitude = head->z;
			t_node start = create_project_node(tv.axis,tv.ordinate,tv.altitude,color,map);
			arr_height[tv.ordinate] = tv.altitude;
			// Draw horizontal line - end
			if (head->next)
				head = head->next;
			tv.altitude = head->z;
			arr_height[tv.ordinate + 1] = tv.altitude;
			color = get_altitude_color(map, head->z);
			t_node end = create_project_node(tv.axis,tv.ordinate+1,tv.altitude,color,map);
			arr_height[tv.ordinate + 1] = tv.altitude;
			if(tv.ordinate != map->width - 1) 
					draw_line(start, end, canvas);
			
			if (tv.axis != 0)
			{
				tv.altitude = prev_height[tv.ordinate];
				color = get_altitude_color(map, tv.altitude);
				end = create_project_node(tv.axis-1,tv.ordinate,tv.altitude,color,map);
				draw_line(start, end, canvas);
				}
			tv.ordinate++;
		}
		int i = 0;
		while (i < map->width)
		{
			prev_height[i] = arr_height[i];
			i++;
		}
		tv.ordinate = 0;
		tv.axis +=1;
	}
}
