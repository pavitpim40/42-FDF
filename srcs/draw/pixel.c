/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:32:23 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/19 15:07:13 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_pixel_color(t_node start, t_node end, t_bsh *b, int pixel)
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
