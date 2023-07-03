/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:48:49 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/04 00:23:02 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "get_next_line.h"
#include "mlx.h"
#include "libft.h"
#include <limits.h>
#include <errno.h>
#include <stdio.h>





int main(int ac, char **av)
{
	// MINI LIBX
	t_canvas canvas;
	t_fdf *f;

	f = malloc(sizeof(t_fdf));
	f->mlx = mlx_init();
	f->win = mlx_new_window(f->mlx, 1920, 1080, "FDF");

	// CANVAS
	canvas.img = mlx_new_image(f->mlx, 1920, 1080);
	canvas.addr = mlx_get_data_addr(canvas.img, &canvas.bits_per_pixel, &canvas.line_length,
									&canvas.endian);
	f->canvas = &canvas;

	// MAP
	t_map *map;
	map = map_init();
	f->map = map;

	int fd;
	fd = open(av[ac-1], O_RDONLY);
	printf("fd : %d\n", fd);
	read_map(fd, map);

	t_coordinate *head = *map->coordinate_map;
	// print_map(map, head);

	// WIRE FRAME SIZE
	// int cell_size = cal_cell_size(map);
	// cell_size = 40;


	// DRAW IMAGE
	draw_image(f->map, head, f->canvas);

	mlx_put_image_to_window(f->mlx, f->win, canvas.img, 0, 0);
	mlx_loop(f->mlx);
}

// 	while (y_start < y_end)