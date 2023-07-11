/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rerender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:08:39 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/11 22:17:33 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rerender(t_fdf *f)
{
	mlx_destroy_image (f->mlx, f->canvas->img);
	free(f->canvas);
	f->canvas = init_canvas(f->mlx);
	draw_image(f);
	render_image(f);
}