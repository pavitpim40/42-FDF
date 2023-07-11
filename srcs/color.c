/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:31:07 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/11 16:24:06 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/color.h"
#include "libft.h"

static int	cal_avg(int start, int end, double percentage)
{
	return ((int)((percentage) * start + (1 - percentage) * end));
}

int	get_altitude_color(t_map *map, int z)
{
	int		color;
	double	percentage;

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

int	get_pixel_color(t_node start, t_node end, t_bresenham *b, int pixel)
{
	double	p;
	int		red;
	int		green;
	int		blue;
	double	diff;

	diff = (double)(pixel - b->start_pixel);
	if (diff < 0)
		diff *= -1;
	p = diff / b->dp;
	if (start.altitude == end.altitude)
		return (start.color);
	red = cal_avg((end.color >> 16) & 0xFF, (start.color >> 16) & 0xFF, p);
	green = cal_avg((end.color >> 8) & 0xFF, (start.color >> 8) & 0xFF, p);
	blue = cal_avg(end.color & 0xFF, start.color & 0xFF, p);
	return ((red << 16) | (green << 8) | blue);
}
