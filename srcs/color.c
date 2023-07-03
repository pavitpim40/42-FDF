/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:31:07 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/03 21:06:15 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/fdf.h"
#include "../includes/color.h"
#include "libft.h"



int get_altitude_color(t_map *map,int z )
{
	int color;
	double percentage;


	percentage = (double)(z - map->z_min) / map->z_range;
	if (percentage < 0.2)
		color = COLOR_DISCO;
	else if (percentage < 0.4)
		color = COLOR_BRICK_RED;
	else if (percentage < 0.6)
		color = COLOR_FLAMINGO;
	else if (percentage < 0.8)
		color = COLOR_JAFFA;
	else
		color = COLOR_SAFFRON;


	return (color);
}


int get_light(int start, int end, double percentage)
{
	return ((int)((percentage) * start + (1-percentage) * end));
}

int get_pixel_color(t_node start, t_node end, int pixel_range, int pixel, int start_pixel)
{
	double percentage;
	
	percentage = (double)(pixel - start_pixel) / pixel_range;
	// printf("percentage : %f\n", percentage);
	if(start.altitude == end.altitude)
		return (start.color);
	if (start.altitude < end.altitude) {
		// percentage = (double)pixel / pixel_range;
		printf("percentage : %f\n", percentage);

		// return color as bit sd
		int red = get_light((start.color >> 16) & 0xFF, (end.color >> 16) & 0xFF, percentage);
		int green = get_light((start.color >> 8) & 0xFF, (end.color >> 8) & 0xFF, percentage);
		int blue = get_light(start.color & 0xFF, end.color & 0xFF, percentage);
		return ((red << 16) | (green << 8) | blue);
		
	}
		
	else {
		printf("percentage : %f\n", percentage);
		// return color as bit shift
		int red = get_light((end.color >> 16) & 0xFF, (start.color >> 16) & 0xFF, percentage);
		int green = get_light((end.color >> 8) & 0xFF, (start.color >> 8) & 0xFF, percentage);
		int blue = get_light(end.color & 0xFF, start.color & 0xFF, percentage);
		return ((red << 16) | (green << 8) | blue);
	}
		
}

