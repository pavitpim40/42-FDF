/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:57:52 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/03 23:23:47 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int cal_cell_size (t_map *map)
{
	int cell_width = (WIDTH - 100) / map->width;
	int cell_height = (HEIGHT - 100) / map->height;
	if(cell_width <	cell_height)
		return (cell_width);
	return (cell_height);
}

/*
** my draw image strategy
** - draw from left to right each row
** - draw only horizontal line for first row
** - draw horizontal line with vertical line to previous for for the rest 
**   while traverse left to right
*/

void draw_image (t_map *map, t_coordinate *head, t_canvas *canvas)
{
	int axis = 0;
	int ordinate = 0;
	int arr_height[map->width];
	int prev_height[map->width];
	int cell_size = cal_cell_size(map);
	cell_size = 50;
	t_node t;
	
	while (axis < map->height)
	{
		while (ordinate < map->width && head)
		{	
			// Draw horizontal line - start 
			t.x = 700 + (cell_size * ordinate);
			t.y = -50 + (cell_size * axis);
			t.z = (head->z) * 10;
			
			int color = get_altitude_color(map, head->z);
			t_node start = create_render_node(t.x, t.y, t.z, color , t.z/10, map);
			arr_height[ordinate] = t.z;

			// Draw horizontal line - end
			if (head->next)
				head = head->next;
			t.x += cell_size;
			t.z = (head->z) * 10;
		
			arr_height[ordinate + 1] = t.z;
			color = get_altitude_color(map, head->z);
			t_node end = create_render_node(t.x, t.y, t.z, color , t.z/10, map);
	
			arr_height[ordinate + 1] = t.z;

		
			if(ordinate != map->width - 1)
				draw_line(start, end, canvas);
			if (axis != 0)
			{
				t.x -= cell_size;
				t.y -= cell_size;
				t.z = prev_height[ordinate];
				
				color = get_altitude_color(map, t.z/10);

				end = create_render_node(t.x, t.y, t.z, color , t.z/10, map);
				draw_line(start, end, canvas);

				// วาดเส้นขอบขวาสุด
				if (ordinate += 1 == map->width)
				{
					t.x += cell_size;
					t.z = prev_height[ordinate + 1];

				
					color = get_altitude_color(map, t.z/10);

					end = create_render_node(t.x, t.y, t.z, color , t.z/10, map);

					t.y += cell_size;
					t.z = arr_height[ordinate + 1];
					
				
					color = get_altitude_color(map, t.z/10);
					start = create_render_node(t.x, t.y, t.z, color , t.z/10, map);
				if(ordinate != map->width - 1)
					// draw_algorithm_3(start.x, start.y, end.x, end.y, &canvas, color);
					draw_line(start, end, canvas);
				}
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
