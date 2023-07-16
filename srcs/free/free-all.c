/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free-all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:55:20 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 19:09:26 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// NEED TO Review
void	free_fdf(t_fdf *f)
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