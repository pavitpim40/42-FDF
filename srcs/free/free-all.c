/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free-all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:55:20 by ppimchan          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/07/19 15:07:48 by ppimchan         ###   ########.fr       */
=======
/*   Updated: 2023/07/17 15:09:56 by ppimchan         ###   ########.fr       */
>>>>>>> arr
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_fdf(t_fdf *f)
{
	if (f->canvas->img)
		mlx_destroy_image(f->mlx, f->canvas->img);
	if (f->canvas)
		free(f->canvas);
	if (f->win)
	{
		mlx_clear_window(f->mlx, f->win);
		mlx_destroy_window(f->mlx, f->win);
	}
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

void	free_mlx(t_fdf *f)
{
	if (f->canvas->img)
		mlx_destroy_image(f->mlx, f->canvas->img);
	if (f->canvas)
		free(f->canvas);
	if (f->win)
		mlx_destroy_window(f->mlx, f->win);
	free(f);
}
