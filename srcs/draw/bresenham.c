/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:13:50 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 20:17:40 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	cal_diff(t_node start, t_node end, t_bresenham *b)
{
	b->dx = cal_abs(start.x, end.x);
	b->dy = cal_abs(start.y, end.y);
	b->step = 1;
	b->dp = cal_max(b->dx, b->dy);
	b->ds = cal_min(b->dx, b->dy);
}

static void	x_dominate(t_node start, t_node end, t_bresenham *b)
{
	b->primary_k = start.x;
	b->primary_n = end.x;
	b->secondary_k = start.y;
	if (b->primary_k > b->primary_n)
		b->direction = -1;
	else
		b->direction = 1;
	if (b->secondary_k > cal_min(start.y, end.y))
		b->step = -1;
}

static void	y_dominate(t_node start, t_node end, t_bresenham *b)
{
	b->primary_k = start.y;
	b->primary_n = end.y;
	b->secondary_k = start.x;
	if (b->primary_k > b->primary_n)
	{
		b->direction = -1;
	}
	else
		b->direction = 1;
	if (b->secondary_k > cal_min(start.x, end.x))
		b->step = -1;
}

t_bresenham	*init_bresenham(t_node start, t_node end)
{
	t_bresenham	*b;

	b = malloc(sizeof(t_bresenham));
	if (!b)
		return (NULL);
	cal_diff(start, end, b);
	if (b->dx >= b->dy)
		x_dominate(start, end, b);
	else
		y_dominate(start, end, b);
	b->decision_param = 2 * b->ds - b->dp;
	b->start_pixel = b->primary_k;
	return (b);
}
