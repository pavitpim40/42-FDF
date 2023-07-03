/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 01:56:30 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/03 20:48:56 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

double percent(int start, int end, int current)
{
	double placement;
	double distance;

	// printf("start : %d\n", start);
	// printf("end : %d\n", end);
	placement = current - start;
	distance = end-start;
	// printf("placement : %f\n", placement);
	// printf("distance : %f\n", distance);
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int get_light(int start, int end, double percentage)
{
	return ((int)((percentage) * start + (1-percentage) * end));
}

// get_gradient_color
int get_gradient_color(t_node start, t_node end, t_node current, int dx, int dy)
{
	double percentage;
	int red;
	int green;
	int blue;

	if (current.color == end.color)
		return (current.color);
	if (dx > dy)
	{
	
		percentage = percent(start.x, end.x, current.x);
	}

	else
	{
		
		percentage = percent(start.y, end.y, current.y);
	}
	// printf("percentage : %f\n\n", percentage);

	red = get_light((start.color >> 16) & 0xFF, (end.color >> 16) & 0xFF, percentage);
	green = get_light((start.color >> 8) & 0xFF, (end.color >> 8) & 0xFF, percentage);
	blue = get_light(start.color & 0xFF, end.color & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
	// return (blue | (green << 8) | (red << 16));
}


// int	get_light(int start, int end, double percentage)
// {
// 	return ((int)((1 - percentage) * start + percentage * end));
// }

int get_iterate_color(t_node start, t_node end, int pixel_range, int pixel, int start_pixel)
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


// Generalize Draw line Algorithm
void draw_line(t_node start, t_node end, t_canvas *img)
{

	// // print node detail
	// // printf("from (%d, %d, %d) to (%d, %d, %d)\n", start.x, start.y, start.z, end.x, end.y, end.z);
	// printf("\nstart altitude : %d\n", start.altitude);
	// printf("end altitude : %d\n", end.altitude);

	// // calc range of altitude
	// int altitude_range = cal_abs(start.altitude, end.altitude);
	// int base_color = start.altitude > end.altitude ? start.color : end.color;
	// printf("altitude_range : %d\n", altitude_range);
	// printf("start color : %d\n", start.color);
	// printf("end color : %d\n", end.color);

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
			// int color = (primary_k / dp )* altitude_range + base_color;
			// int color = get_gradient_color(start, end, duplicate_node(primary_k, secondary_k, 0, 0), dx, dy);
			int color = get_iterate_color(start, end, dx, primary_k,start_pixel);
			my_mlx_pixel_put(img, primary_k, secondary_k, color);
		}

		else
		{

			// int color = (primary_k / dp )* altitude_range + base_color;
			// int color = get_gradient_color(start, end, duplicate_node(secondary_k, primary_k, 0, 0), dx, dy);
			int color = get_iterate_color(start, end, dy, primary_k,start_pixel);
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