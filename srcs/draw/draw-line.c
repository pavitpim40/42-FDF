/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw-line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 01:56:30 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/14 17:15:46 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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

void	draw_line(t_node start, t_node end, t_canvas *img)
{
	t_bresenham	*p;
	int			color;

	p = init_bresenham(start, end);
	while (p->primary_k != p->primary_n)
	{
		color = get_pixel_color(start, end, p, p->primary_k);
		if (p->dx >= p->dy)
			pixel_put(img, p->primary_k, p->secondary_k, color);
		else
			pixel_put(img, p->secondary_k, p->primary_k, color);
		p->primary_k += p->direction;
		if (p->decision_param < 0)
			p->decision_param = p->decision_param + (2 * p->ds);
		else
		{
			p->decision_param = p->decision_param + (2 * p->ds) - (2 * p->dp);
			p->secondary_k += p->step;
		}
	}
	color = get_pixel_color(start, end, p, p->primary_k);
	if (p->dx >= p->dy)
		pixel_put(img, p->primary_k, p->secondary_k, color);
	else
		pixel_put(img, p->secondary_k, p->primary_k, color);
}
