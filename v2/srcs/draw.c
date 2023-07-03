/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 01:56:30 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/03 14:06:50 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

double percent(int start, int end, int current)
{
    double placement;
    double distance;

    placement = current - start;
    distance = end - start;
    return ((distance == 0) ? 1.0 : (placement / distance));
}

int get_light(int start, int end, double percentage)
{
    return ((int)((1 - percentage) * start + percentage * end));
}

// get_gradient_color
int get_gradient_color(t_node start,t_node end, t_node current, int dx,int dy)
{
	double percentage;
	int red;
	int green;
	int blue;

	if(current.color == end.color)
		return (current.color);
	if (dx > dy)
		percentage = percent(start.x, end.x, current.x);
	else
		percentage = percent(start.y, end.y, current.y);

	red = get_light((start.color >> 16) & 0xFF, (end.color >> 16) & 0xFF, percentage);
	green = get_light((start.color >> 8) & 0xFF, (end.color >> 8) & 0xFF, percentage);
	blue = get_light(start.color & 0xFF, end.color & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);

}

// Generalize Draw line Algorithm
void draw_line(t_node start,t_node end, t_canvas *img)
{
	int dx = cal_abs(start.x, end.x);
	int dy = cal_abs(start.y, end.y);
	int step = 1;

	// #2 Calc step
	int primary_k;
	int primary_n;
	int secondary_k;
	int dp = cal_max(dx, dy);
	int ds = cal_min(dx, dy);

	

	if (dx >= dy)
	{
		primary_k = cal_min(start.x, end.x);
		primary_n = cal_max(start.x, end.x);
		secondary_k = primary_k == start.x ? start.y : end.y;
		if (secondary_k > cal_min(start.y, end.y))
			step = -1;
	
	}
	else
	{
		primary_k = cal_min(start.y, end.y);
		primary_n = cal_max(start.y, end.y);
		secondary_k = primary_k == start.y ? start.x : end.x;
		if (secondary_k > cal_min(start.x, end.x))
			step = -1;
	
	}

	int decision_parameter = 2 * ds - dp;

	while (primary_k <= primary_n)
	{ // change** yk <= yn

		if (dx >= dy)
		{
			my_mlx_pixel_put(img, primary_k, secondary_k, get_gradient_color(start, end, duplicate_node(primary_k, secondary_k, 0, 0), dx, dy));
		}

		else
		{
			my_mlx_pixel_put(img, secondary_k, primary_k, get_gradient_color(start, end, duplicate_node(primary_k, secondary_k, 0, 0), dx, dy));
		}

		primary_k += 1; // ***change
		if (decision_parameter < 0)
		{
			decision_parameter = decision_parameter + (2 * ds);
		}
		else
		{
			decision_parameter = decision_parameter + (2 * ds) - (2 * dp);
			secondary_k += step; // ***change
		}
	}
}