/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw-pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 01:59:15 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 13:44:49 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	draw_pixel(t_canvas *canvas, int x, int y, int color)
{
	char	*pos;
	// printf("pixel-color: %x\n", color);
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pos = canvas->addr + (y * canvas->line_length + x * (canvas->bbp / 8));
		*(unsigned int *)pos = color;
		// *(unsigned int *)(++pos) = color >> 8;
		// *(unsigned int *)(++pos) = color >> 16;
	
	}
}
