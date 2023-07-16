/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw-line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 01:56:30 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 13:48:48 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	draw_pixel_new(t_canvas *canvas, int x, int y)
{
	char	*pos;
	// printf("pixel-color: %x\n", color);
	int	color = COLOR_SAFFRON;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pos = canvas->addr + (y * canvas->line_length + x * (canvas->bbp / 8));
		*(unsigned int *)pos = color;
		// *(unsigned int *)(++pos) = color >> 8;
		// *(unsigned int *)(++pos) = color >> 16;
	
	}
}

void	draw_line(t_node start, t_node end, t_canvas *img)
{
	t_bresenham	*p;
	int			color;

	p = init_bresenham(start, end);

	// printf("\nstart-color: %x\n", start.color);
	// printf("end-color: %x\n", end.color);
	
	while (p->primary_k != p->primary_n)
	{
		color = get_pixel_color(start, end, p, p->primary_k);
		// printf("print color: %x\n", color);
		// printf("actual color: %x\n",COLOR_SAFFRON);
		// printf("PRINT COLOR: %X\n", color);
		// printf("ACTUAL COLOR: %X\n",COLOR_SAFFRON);
		
		
		// printf("secondary_k: %d\n", p->secondary_k);
		// printf("\npx: %d, py: %d\n", p->dx, p->dy);
		// printf("primary_k: %d\n", p->primary_k);
		// printf("primary_n: %d\n", p->primary_n);
		if (p->dx >= p->dy)
			draw_pixel(img, p->primary_k, p->secondary_k, color);
		else
			draw_pixel(img, p->secondary_k, p->primary_k, color);
		p->primary_k += p->direction;
		if (p->decision_param < 0)
			p->decision_param = p->decision_param + (2 * p->ds);
		else
		{
			p->decision_param = p->decision_param + (2 * p->ds) - (2 * p->dp);
			p->secondary_k += p->step;
		}
	}
	// color = get_pixel_color(start, end, p, p->primary_k);
	// if (p->dx >= p->dy)
	// 	draw_pixel(img, p->primary_k, p->secondary_k, color);
	// else
	// 	draw_pixel(img, p->secondary_k, p->primary_k, color);
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
