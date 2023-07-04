/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 01:56:30 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/04 17:17:43 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void cal_diff(t_node start, t_node end, t_bresenham *b)
{
	b->dx = cal_abs(start.x, end.x);
	b->dy = cal_abs(start.y, end.y);
	b->step = 1;
	b->dp = cal_max(b->dx, b->dy);
	b->ds = cal_min(b->dx, b->dy);
}

static void x_dominate(t_node start, t_node end, t_bresenham *b)
{
	// printf("x_dominate\n");
	b->primary_k = cal_min(start.x, end.x);
	b->primary_n = cal_max(start.x, end.x);
	if (b->primary_k == start.x)
		b->secondary_k = start.y;
	else
		b->secondary_k = end.y;
	if (b->secondary_k > cal_min(start.y, end.y))
		b->step = -1;
}

static void y_dominate(t_node start, t_node end, t_bresenham *b)
{
	// printf("y_dominate\n");
	b->primary_k = cal_min(start.y, end.y);
	b->primary_n = cal_max(start.y, end.y);
	if (b->primary_k == start.y)
		b->secondary_k = start.x;
	else
		b->secondary_k = end.x;
	if (b->secondary_k > cal_min(start.x, end.x))
		b->step = -1;
}

static t_bresenham *init_bresenham(t_node start, t_node end)
{
	t_bresenham *b;

	b = malloc(sizeof(t_bresenham));
	if (!b)
		return (NULL);
	cal_diff(start, end, b);
	if (b->dx >= b->dy)
		x_dominate(start, end, b);
	else
		y_dominate(start, end, b);
	b->decision_parameter = 2 * b->ds - b->dp;
	b->start_pixel = b->primary_k;
	return (b);
}

void draw_line(t_node start, t_node end, t_canvas *img, int count)
{
	t_bresenham *p;

	p = init_bresenham(start, end);
	printf("count : %d\n", count);
	printf("start.x : %d, start.y : %d\n", start.x, start.y);
	printf("end.x : %d, end.y : %d\n", end.x, end.y);
	printf("altitude start : %d, altitude end : %d\n", start.altitude, end.altitude);
	printf("start color : %X, end color : %X\n", start.color, end.color);
	if (count == 6){
		printf("p->dx : %d, p->dy : %d\n", p->dx, p->dy);
		printf("p->primary_k : %d, p->primary_n : %d\n", p->primary_k, p->primary_n);
	}
	printf("\n");
		
	while (p->primary_k <= p->primary_n)
	{
		int color = get_pixel_color(start, end, p, p->primary_k);
		if (p->dx >= p->dy)
		{
			
			pixel_put(img, p->primary_k, p->secondary_k, color);
		}
		else
		{
			
			pixel_put(img, p->secondary_k, p->primary_k, color);
		}
		p->primary_k += 1; // ***change
		if (p->decision_parameter < 0)
			p->decision_parameter = p->decision_parameter + (2 * p->ds);
		else
		{
			p->decision_parameter = p->decision_parameter + (2 * p->ds) - (2 * p->dp);
			p->secondary_k += p->step; // ***change
		}
	}
}