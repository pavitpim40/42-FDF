/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:48:49 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/03 22:58:48 by ppimchan         ###   ########.fr       */
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
	void *mlx;
	void *mlx_win;
	t_canvas canvas;

	// FOR START MLX
	mlx = mlx_init();

	// FOR START WINDOW
	mlx_win = mlx_new_window(mlx, 1920, 1080, "FDF");

	// FOR START IMAGE
	canvas.img = mlx_new_image(mlx, 1920, 1080);
	canvas.addr = mlx_get_data_addr(canvas.img, &canvas.bits_per_pixel, &canvas.line_length,
									&canvas.endian);

	// MAP
	t_map *map;
	map = map_init();

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
	draw_image(map, head, &canvas);

	mlx_put_image_to_window(mlx, mlx_win, canvas.img, 0, 0);
	mlx_loop(mlx);
}

// 	while (y_start < y_end)