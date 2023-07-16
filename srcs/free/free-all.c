/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free-all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:55:20 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/17 01:39:29 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// NEED TO Review
void	free_fdf(t_fdf *f)
{
	if (f->canvas->img)
		mlx_destroy_image(f->mlx, f->canvas->img);
	if (f->canvas)
		free(f->canvas);
	if (f->win)
		mlx_destroy_window(f->mlx, f->win);
	if (f->map)
		free(f->map);
	if (f->c_mtx)
		free(f->c_mtx);
	if (f->h_mtx)
		free(f->h_mtx);
	if (f->camera)
		free(f->camera);
	free(f);
}

void	free_all(t_fdf *f)
{
	if (f->canvas)
		free(f->canvas);
	if (f->win)
		free(f->win);
	if (f->mlx)
		free(f->mlx);
	if (f->map)
		free(f->map);
	if (f->camera)
		free(f->camera);
	free(f);
}
