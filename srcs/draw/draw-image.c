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



void draw_image (t_fdf *fdf)
{
	t_matrix tv; // tv = traverse
	int arr_height[fdf->map->width];
	int prev_height[fdf->map->width];
	t_matrix *tmp;

	tv.axis = 0;
	tv.ordinate = 0;
	tmp =  fdf->head;
	
	// int color;
	while (tv.axis < fdf->map->height)
	{
		while (tv.ordinate < fdf->map->width  && fdf->head)
		{	
			// printf("new Draw\n");
			t_node start = new_render_node(fdf,tv.axis,tv.ordinate,fdf->head->z);
			arr_height[tv.ordinate] = fdf->head->z;
			// Draw horizontal line - end
			if (fdf->head->next)
				fdf->head = fdf->head->next;
			arr_height[tv.ordinate + 1] = fdf->head->z;;
			t_node end = new_render_node(fdf,tv.axis,tv.ordinate+1,fdf->head->z);
		
			if(tv.ordinate != fdf->map->width - 1) 
					draw_line(start, end, fdf->canvas);
			if (tv.axis != 0)
			{
				tv.altitude = prev_height[tv.ordinate];
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
}
