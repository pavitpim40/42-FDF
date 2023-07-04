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

int cal_cell_size (t_map *map)
{
	int cell_width = (WIDTH - 100) / map->width;
	int cell_height = (HEIGHT - 100) / map->height;
	if(cell_width <	cell_height)
		return (cell_width);
	return (cell_height);
}

// t_node draw_right(t_map *m, t_canvas *c, t_node *t, t_coordinate *h, int *arr_h)
// {
// 	t->x = (WIDTH/2) + (m->cell_size * h->x);
// 	printf("x = %d\n", t->x);
// 	t->y = -50 + (m->cell_size * h->y);
// 	t->z = (h->z) * 10;
// 	int color = get_altitude_color(m, h->z);
// 	t_node start = create_render_node(*t,color , t->z/10, m);

// 	if(h->next)
// 		h = h->next;
// 	t->x += m->cell_size;
// 	t->z = (h->z) * 10;
// 	arr_h[h->x + 1] = t->z;
// 	color = get_altitude_color(m, h->z);
// 	t_node end = create_render_node(*t, color , t->z/10, m);
// 	arr_h[h->x + 1] = t->z;
// 	if(h->x != m->width - 1)
// 		draw_line(start, end, c);
// 	return (start);
// }

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
	int cell_size = cal_cell_size(map);
	cell_size = 50;
	t_node *t; // traverse coordinate
	int color;

	t = malloc(sizeof(t_node));
	if (!t)
		terminate(ERR_MAP_INIT);

	// how to calculate start x and y
	int W_CONTENT = WIDTH - 800;
	// int H_CONTENT = HEIGHT - 200;
	 int cell_w = W_CONTENT / map->width;
	int start_x = (WIDTH - W_CONTENT) / 2  + cell_size / 2;

	int H_CONTENT = HEIGHT - 600;
	int cell_h = H_CONTENT / map->height;
	int start_y = (HEIGHT - H_CONTENT) / 2  + cell_size / 2;

	

	if(cell_w <	cell_h) {
	cell_size = cell_w;
		start_y = (HEIGHT - (cell_size * map->height)) / 2;
	}
	else{
		cell_size = cell_h;
		start_x = (WIDTH - (cell_size * map->width)) / 2;
	}
	printf("start_x = %d\n", start_x);
	printf("start_y = %d\n", start_y);
	printf("cell_size = %d\n", cell_size);
	// cal start x and y when isometric
	
		

	while (axis < map->height)
	{
		// printf("axis = %d\n", axis);
		// printf("map-> height = %d\n", map->height);
		while (ordinate < map->width  && head)
		{	
			
			t->x = start_x + (cell_size * ordinate);
			t->y = start_y + (cell_size * axis);
			t->z = (head->z) * 10;
			color = get_altitude_color(map, head->z);
			t_node start = create_project_node(axis,ordinate,head->z,color,map);
			// printf("start x:%d y:%d z:%d \n",start.x,start.y,start.z);
			arr_height[ordinate] = head->z;

			// Draw horizontal line - end
			if (head->next)
				head = head->next;
			// 1st update
			t->x += cell_size;
			t->z = (head->z) * 10;
			arr_height[ordinate + 1] = head->z;
			color = get_altitude_color(map, head->z);
			t_node end = create_project_node(axis,ordinate+1,head->z,color,map);
			// printf("end x:%d y:%d z:%d \n",end.x,end.y,end.z);
			arr_height[ordinate + 1] = head->z;

			if(ordinate != map->width - 1)
				draw_line(start, end, canvas);
			
			// Draw vertical line - BACKWARD
			if (axis != 0)
			{
				// 2nd update
				t->x -= cell_size;
				t->y -= cell_size;
				t->z = prev_height[ordinate];
				int altitude = prev_height[ordinate];
				
				color = get_altitude_color(map, altitude);

				end = create_project_node(axis-1,ordinate,altitude,color,map);
				draw_line(start, end, canvas);

				// วาดเส้นขอบขวาสุด
				if (ordinate += 1 == map->width)
				{
					// 3rd update
					t->x += cell_size;
					t->z = prev_height[ordinate + 1];
					altitude = prev_height[ordinate + 1];
					color = get_altitude_color(map, altitude);
					end = create_project_node(axis,ordinate-1,altitude,color,map);

					// 4th update
					t->y += cell_size;
					t->z = arr_height[ordinate + 1];
					altitude = arr_height[ordinate + 1];
					color = get_altitude_color(map, altitude);
					start = create_project_node(axis,ordinate+1,altitude,color,map);
				// if(ordinate != map->width - 1)
					// draw_line(start, end, canvas);
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
