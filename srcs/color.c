/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:31:07 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/03 22:36:15 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/fdf.h"
#include "../includes/color.h"
#include "libft.h"




static int cal_avg(int start, int end, double percentage)
{
	return ((int)((percentage) * start + (1-percentage) * end));
}


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


int get_pixel_color(t_node start, t_node end, t_bresenham *b, int pixel)
{
	double percentage;
	int red;
	int green;
	int blue;
	
	percentage = (double)(pixel - b->start_pixel) / b->dp;
	if(start.altitude == end.altitude)
		return (start.color);
	if (start.altitude < end.altitude) {
		red = cal_avg((start.color >> 16) & 0xFF, (end.color >> 16) & 0xFF, percentage);
		green = cal_avg((start.color >> 8) & 0xFF, (end.color >> 8) & 0xFF, percentage);
		blue = cal_avg(start.color & 0xFF, end.color & 0xFF, percentage);
		return ((red << 16) | (green << 8) | blue);
	}
		
	else {
		red = cal_avg((end.color >> 16) & 0xFF, (start.color >> 16) & 0xFF, percentage);
		green = cal_avg((end.color >> 8) & 0xFF, (start.color >> 8) & 0xFF, percentage);
		blue = cal_avg(end.color & 0xFF, start.color & 0xFF, percentage);
		return ((red << 16) | (green << 8) | blue);
	}
}

