/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 01:56:30 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/03 03:49:24 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// Generalize Draw line Algorithm
void draw_algorithm_3(int x0, int y0, int xn, int yn, t_canvas *img, int color)
{
	int dx = cal_abs(x0, xn);
	int dy = cal_abs(y0, yn);
	int step = 1;

	// #2 Calc step
	int primary_k;
	int primary_n;
	int secondary_k;
	int dp = cal_max(dx, dy);
	int ds = cal_min(dx, dy);

	// printf("dx : %d\n", dx);
	// printf("dy : %d\n", dy);

	if (dx >= dy)
	{
		primary_k = cal_min(x0, xn);
		primary_n = cal_max(x0, xn);
		secondary_k = primary_k == x0 ? y0 : yn;
		if (secondary_k > cal_min(y0, yn))
			step = -1;
		// printf("X dominate\n");
	}
	else
	{
		primary_k = cal_min(y0, yn);
		primary_n = cal_max(y0, yn);
		secondary_k = primary_k == y0 ? x0 : xn;
		if (secondary_k > cal_min(x0, xn))
			step = -1;
		// printf("Y dominate\n");
	}
	// printf("primary_k : %d\n", primary_k);
	// printf("primary_n : %d\n", primary_n);
	// printf("secondary_k : %d\n", secondary_k);

	int decision_parameter = 2 * ds - dp;

	while (primary_k <= primary_n)
	{ // change** yk <= yn

		if (dx >= dy)
		{
			// printf("Pair : (%d,%d)\n", primary_k, secondary_k);
			my_mlx_pixel_put(img, primary_k, secondary_k, color);
		}

		else
		{
			my_mlx_pixel_put(img, secondary_k, primary_k, color);
			// printf("Pair : (%d,%d)\n", primary_k, secondary_k);
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
	// printf("endline-------------------\n");
}