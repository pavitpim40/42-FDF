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
#include "mlx.h"

t_coordinate dup_coordinate(int axis,int ordinate,int altitude, int color)
{
	t_coordinate new_node;
	new_node.axis = axis;
	new_node.ordinate = ordinate;
	new_node.altitude = altitude;
	new_node.color = color;
	return (new_node);
}

/*
** my draw image strategy
** - draw from left to right each row
** - draw only horizontal line for first row
** - draw horizontal line with vertical line to previous for for the rest 
**   while traverse left to right
*/

// void draw_horizontal_raster(t_fdf *fdf,  t_coordinate *head, t_coordinate tv)
// {
// 	int color = get_altitude_color(fdf->map, head->z);
// 	tv.altitude = head->z;
// 	t_coordinate tmp = dup_coordinate(tv.axis,tv.ordinate,tv.altitude,color);
// 	t_node start = coordinate_to_pixel(fdf,tmp,color);
			
// }

t_node new_render_node (t_fdf *fdf,int axis,int ordinate,int altitude)
{
	t_coordinate tmp;
	int color;
	
	color  = get_altitude_color(fdf->map, altitude);
	tmp = dup_coordinate(axis,ordinate,altitude,color);
	// printf("x:%d y:%d z:%d color:%d\n",tmp.axis,tmp.ordinate,tmp.altitude,tmp.color);
	t_node start = coordinate_to_pixel(fdf,tmp,color);
	return (start);
}

void draw_image (t_fdf *fdf)
{
	// Shared Data
	t_coordinate tv; // tv = traverse
	int arr_height[fdf->map->width];
	int prev_height[fdf->map->width];
	t_coordinate *tmp;

	tv.axis = 0;
	tv.ordinate = 0;
	tmp =  fdf->head;
	
	// int color;
	while (tv.axis < fdf->map->height)
	{
		while (tv.ordinate < fdf->map->width  && fdf->head)
		{	
			printf("new Draw\n");
			t_node start = new_render_node(fdf,tv.axis,tv.ordinate,fdf->head->z);
			arr_height[tv.ordinate] = fdf->head->z;
			// Draw horizontal line - end
			if (fdf->head->next)
				fdf->head = fdf->head->next;
			arr_height[tv.ordinate + 1] = fdf->head->z;;
			t_node end = new_render_node(fdf,tv.axis,tv.ordinate+1,fdf->head->z);
			printf("s:(%d,%d) -- สูง:%d\n",start.x,start.y,arr_height[tv.ordinate]);
			printf("e:(%d,%d) -- สูง:%d\n\n",end.x,end.y,arr_height[tv.ordinate+1]);
			if(tv.ordinate != fdf->map->width - 1) 
					draw_line(start, end, fdf->canvas);
			if (tv.axis != 0)
			{
				tv.altitude = prev_height[tv.ordinate];
				printf("start-in (%d,%d) -- z:%d \n",start.x,start.y,arr_height[tv.ordinate]);
			printf("end-in (%d,%d) -- z:%d \n",end.x,end.y,prev_height[tv.ordinate]);
				
				end = new_render_node(fdf,tv.axis - 1,tv.ordinate,tv.altitude);
				draw_line(start, end, fdf->canvas);
			}
			tv.ordinate++;
		}
		int i = 0;
		while (i < fdf->map->width)
		{
			prev_height[i] = arr_height[i];
			i++;
		}
		tv.ordinate = 0;
		tv.axis +=1;
	
	}
	fdf->head = tmp;
	// mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->canvas->img, 0, 0);
	printf("draw image done\n");
}
