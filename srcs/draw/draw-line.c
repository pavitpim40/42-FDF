/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw-line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 01:56:30 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 23:39:00 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	draw_line(t_node start, t_node end, t_canvas *img)
{
	t_bsh		*p;
	int			color;

	p = init_bsh(start, end);
	while (p->primary_k != p->primary_n)
	{
		color = get_pixel_color(start, end, p, p->primary_k);
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
	color = get_pixel_color(start, end, p, p->primary_k);
	if (p->dx >= p->dy)
		draw_pixel(img, p->primary_k, p->secondary_k, color);
	else
		draw_pixel(img, p->secondary_k, p->primary_k, color);
}
