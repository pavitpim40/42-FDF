/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:47:42 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 23:08:04 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reset(t_fdf *f)
{
	f->camera->zoom = cal_min(WIDTH / (f->map->width * 2), \
			HEIGHT / (f->map->height * 2));
	f->camera->alpha = 0;
	f->camera->beta = 0;
	f->camera->gamma = 0;
	f->camera->z_divisor = 3;
	f->camera->x_offset = 0;
	f->camera->y_offset = 0;
	f->camera->projection = ISOMETRIC;
	rerender(f);
}
