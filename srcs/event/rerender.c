/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rerender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:08:39 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/14 14:27:16 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rerender(t_fdf *f)
{
	t_canvas	*canvas;

	canvas = f->canvas;
	mlx_destroy_image (f->mlx, f->canvas->img);
	f->canvas->img = mlx_new_image(f->mlx, 1920, 1080);
	f->canvas->addr = mlx_get_data_addr(canvas->img, &(canvas->bbp), \
		&(canvas->line_length), &(canvas->endian));
	draw_image(f);
	render_image(f);
}