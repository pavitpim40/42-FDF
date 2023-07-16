/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create-matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 00:23:43 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/17 01:24:50 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	write_matrix(t_fdf *f, int *altitude_mtx, int *color_mtx)
{
	int		i;
	t_point	*current;
	t_point	*tmp;

	i = 0;
	current = f->start;
	tmp = current;
	while (current)
	{
		altitude_mtx[i] = current->altitude;
		color_mtx[i] = current->default_color;
		tmp = current;
		current = current->next;
		free(tmp);
		i++;
	}
	f->h_mtx = altitude_mtx;
	f->c_mtx = color_mtx;
}

void	create_matrix(t_fdf *f)
{
	int	*altitude_mtx;
	int	*color_mtx;

	altitude_mtx = (int *)malloc(sizeof(int) * f->map->width * f->map->height);
	color_mtx = (int *)malloc(sizeof(int) * f->map->width * f->map->height);
	printf("## h_mtx %p\n", altitude_mtx);
	printf("## c_mtx %p\n", color_mtx);
	if (!altitude_mtx || !color_mtx)
	{
		free(altitude_mtx);
		if (color_mtx)
			free(color_mtx);
		free_fdf(f);
	}
	write_matrix(f, altitude_mtx, color_mtx);
}
