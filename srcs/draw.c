/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 01:56:30 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/03 21:06:35 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"




// Generalize Draw line Algorithm
void draw_line(t_node start, t_node end, t_canvas *img)
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
	int start_pixel = primary_k;

	while (primary_k <= primary_n)
	{ // change** yk <= yn

		if (dx >= dy)
		{
		
			int color = get_pixel_color(start, end, dx, primary_k,start_pixel);
			my_mlx_pixel_put(img, primary_k, secondary_k, color);
		}

		else
		{

			int color = get_pixel_color(start, end, dy, primary_k,start_pixel);
			my_mlx_pixel_put(img, secondary_k, primary_k, color);
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