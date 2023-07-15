/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create-matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 00:23:43 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 03:02:03 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
void traverse_list_point(t_point *head)
{
	t_point *current;
	int	count; 

	count = 0;
	current = head;
	while (current)
	{
		// printf("altitude: %d, color: %x\n", current->altitude, current->default_color);
		current = current->next;
		count++;
	}
	// printf("count: %d\n", count);
}

void create_matrix(t_fdf *f)
{
	int	*altitude_mtx;
	int	*color_mtx;

	altitude_mtx = (int *)malloc(sizeof(int) * f->map->width * f->map->height);
	color_mtx = (int *)malloc(sizeof(int) * f->map->width * f->map->height);
	if(!altitude_mtx || !color_mtx)
	{
		free(altitude_mtx);
		if (color_mtx)
			free(color_mtx);
		free_all(f);
	}
	t_point *current;
	t_point *tmp;

	current = f->start;
	tmp = current;
	int i = 0;
	while (current)
	{
		altitude_mtx[i] = current->altitude;
		// printf("current color: %x\n", current->default_color);
		color_mtx[i] = current->default_color;
		tmp = current;
		current = current->next;
		free(tmp);
		i++;
	}
	f->h_mtx = altitude_mtx;
	f->c_mtx = color_mtx;

	// loop array
	i = 0;
	// int j = 0;
	// while (i < f->map->height)
	// {
	// 	j = 0;
	// 	while (j < f->map->width)
	// 	{
	// 		// printf("altitude: %d, color: %x\n", f->h_mtx[i * f->map->width + j], f->c_mtx[i * f->map->width + j]);
	// 		// printf("%d ", f->h_mtx[i * f->map->width + j]);
	// 		// printf("%x ", f->c_mtx[i * f->map->width + j]);
	// 		j++;
	// 	}
	// 	// printf("\n");
	// 	i++;
	// }
}