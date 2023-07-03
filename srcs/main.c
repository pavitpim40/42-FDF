/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:48:49 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/03 17:43:23 by ppimchan         ###   ########.fr       */
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

	printf("canvas.addr : %p\n", canvas.addr);
	printf("sizeof canvas.addr : %lu\n", sizeof(canvas.addr));
	printf("canvas->endian : %d\n", canvas.endian);	

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
	int cell_width = (WIDTH - 100) / map->width;
	int cell_height = (HEIGHT - 100) / map->height;
	int cell_size = cell_width < cell_height ? cell_width : cell_height;
	cell_size = 40;


	// DRAW IMAGE
	int axis = 0;
	int ordinate = 0;
	int arr_height[map->width];
	int prev_height[map->width];
	
	while (axis < map->height)
	{
		// Iteration for each t_coordinate 
		while (ordinate < map->width && head)
		{	
			// Draw horizontal line - start 
			int x = 700 + (cell_size * ordinate);
			int y = -50 + (cell_size * axis);
			int z = (head->z) * 10;
			int color = get_altitude_color(map, head->z);
			t_node start = duplicate_node(x, y, z, color);
			arr_height[ordinate] = z;

			// Draw horizontal line - end
			if (head->next)
				head = head->next;
			x += cell_size;
			z = (head->z) * 10;
			arr_height[ordinate + 1] = z;
			color = get_altitude_color(map, head->z);
			t_node end = duplicate_node(x, y, z, color);
	
			arr_height[ordinate + 1] = z;

		
			if(ordinate != map->width - 1)
				draw_line(start, end, &canvas);
			

			
			if (axis != 0)
			{

				x -= cell_size;
				y -= cell_size;
				z = prev_height[ordinate];
				color = get_altitude_color(map, z/10);

				// end = duplicate_node(x, y, z, color);
				end = create_render_node(x, y, z, color , z/10, map);
				// draw_algorithm_3(start.x, start.y, end.x, end.y, &canvas, color);
				draw_line(start, end, &canvas);

				// วาดเส้นขอบขวาสุด
				if (ordinate += 1 == map->width)
				{
					x += cell_size;
					z = prev_height[ordinate + 1];
					color = get_altitude_color(map, z/10);

					end = duplicate_node(x, y, z, color);

					y += cell_size;
					z = arr_height[ordinate + 1];
					color = get_altitude_color(map, z/10);
					start = duplicate_node(x, y, z, color);
				if(ordinate != map->width - 1)
					// draw_algorithm_3(start.x, start.y, end.x, end.y, &canvas, color);
					draw_line(start, end, &canvas);
				}
			}

			ordinate++;
		}

		int i = 0;
		while (i < map->width)
		{
			prev_height[i] = arr_height[i];
			i++;
		}

		ordinate = 0;

		axis++;
	}

	// test_demo(&canvas);

	mlx_put_image_to_window(mlx, mlx_win, canvas.img, 0, 0);
	mlx_loop(mlx);
}

// 	while (y_start < y_end)