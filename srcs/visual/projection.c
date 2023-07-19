/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:19:40 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 23:07:19 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric_projection(t_fdf *f)
{
	f->camera->projection = ISOMETRIC;
	f->camera->alpha = 0;
	f->camera->beta = 0;
	f->camera->gamma = 0;
	f->camera->x_offset = 0;
	f->camera->y_offset = 0;
	rerender(f);
}

void	topview_projection(t_fdf *f)
{
	f->camera->projection = PARALLEL;
	f->camera->alpha = 0;
	f->camera->beta = 0;
	f->camera->gamma = 0;
	f->camera->x_offset = 0;
	f->camera->y_offset = 0;
	rerender(f);
}
