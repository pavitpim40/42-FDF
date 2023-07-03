/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 01:59:15 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/04 02:53:46 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void pixel_put(t_canvas *canvas, int x, int y, int color)
{
	char *pos;


	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pos = canvas->addr + (y * canvas->line_length + x * (canvas->bits_per_pixel / 8));
		*(unsigned int *)pos = color;
		*(unsigned int *)(++pos) = color >> 8;
		*(unsigned int *)(++pos) = color >> 16;
		*(unsigned int *)(++pos) = 0;
	}	
}
