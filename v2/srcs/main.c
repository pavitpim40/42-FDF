/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:48:49 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/03 13:39:21 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "get_next_line.h"
#include "mlx.h"
#include "libft.h"
#include <limits.h>
#include <errno.h>
#include <stdio.h>

void test_demo(t_canvas *canvas)
{

	int x0 = 200;
	int xn = 800;
	int y0 = 200;
	int yn = 800;
	int z0 = 0;
	int zn = 0;
	// create t_node for rectangle
	t_node node_1 = {x0, y0, z0, 0x00FF0000};
	t_node node_2 = {xn, y0, zn, 0x00FF0000};
	t_node node_3 = {xn, yn, zn, 0x00FF0000};
	t_node node_4 = {x0, yn, z0, 0x00FF0000};

	// for Top line - RED
	t_node p1 = project_isometric(duplicate_node(node_1.x, node_1.y, node_1.z, 0x00FF0000));
	t_node p2 = project_isometric(duplicate_node(node_2.x, node_2.y, node_2.z, 0x00FF0000));
	// printf("p1 : (%d,%d)\n", p1.x, p1.y);
	// printf("p2 : (%d,%d)\n", p2.x, p2.y);
	draw_algorithm_3(p1.x, p1.y, p2.x, p2.y, canvas, 0x00FF0000);
	draw_algorithm_3(node_1.x, node_1.y, node_2.x, node_2.y, canvas, 0x00FF0000);

	// for Right Line - ORANGE
	t_node p3 = project_isometric(duplicate_node(node_2.x, node_2.y, node_2.z, 0x00FF0000));
	t_node p4 = project_isometric(duplicate_node(node_3.x, node_3.y, node_3.z, 0x00FF0000));
	// printf("p3 : (%d,%d)\n", p3.x, p3.y);
	// printf("p4 : (%d,%d)\n", p4.x, p4.y);
	draw_algorithm_3(p3.x, p3.y, p4.x, p4.y, canvas, 0x00FFA500);
	draw_algorithm_3(node_2.x, node_2.y, node_3.x, node_3.y, canvas, 0x00FFA500);

	// for Bottom Line - GREEN
	t_node p5 = project_isometric(duplicate_node(node_3.x, node_3.y, node_3.z, 0x0000FF00));
	t_node p6 = project_isometric(duplicate_node(node_4.x, node_4.y, node_4.z, 0x0000FF00));
	// printf("p5 : (%d,%d)\n", p5.x, p5.y);
	// printf("p6 : (%d,%d)\n", p6.x, p6.y);
	draw_algorithm_3(p5.x, p5.y, p6.x, p6.y, canvas, 0x0000FF00);
	draw_algorithm_3(node_3.x, node_3.y, node_4.x, node_4.y, canvas, 0x0000FF00);

	// for Left Line - BLUE
	t_node p7 = project_isometric(duplicate_node(node_4.x, node_4.y, node_4.z, 0x000000FF));
	t_node p8 = project_isometric(duplicate_node(node_1.x, node_1.y, node_1.z, 0x000000FF));
	// printf("p7 : (%d,%d)\n", p7.x, p7.y);
	// printf("p8 : (%d,%d)\n", p8.x, p8.y);
	draw_algorithm_3(p7.x, p7.y, p8.x, p8.y, canvas, 0x000000FF);
	draw_algorithm_3(node_4.x, node_4.y, node_1.x, node_1.y, canvas, 0x000000FF);
}

int main(void)
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
	fd = open("maps/42.fdf", O_RDONLY);
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

		while (ordinate < map->width && head)
		{			
			int x = 700 + (cell_size * ordinate);
			int y = -50 + (cell_size * axis);
			int z = (head->z) * 10;
			int color = get_altitude_color(map, z);
			t_node start = duplicate_node(x, y, z, color);
			arr_height[ordinate] = z;

			if (head->next)
				head = head->next;
			x += cell_size;
			z = (head->z) * 10;
			arr_height[ordinate + 1] = z;
			color = get_altitude_color(map, z);
		
			t_node end = duplicate_node(x, y, z, color);
	
			arr_height[ordinate + 1] = z;

		
			if(ordinate != map->width - 1)
				draw_line(start, end, &canvas, color);
				// draw_algorithm_3(start.x, start.y, end.x, end.y, &canvas, color);

			
			if (axis != 0)
			{

				x -= cell_size;
				y -= cell_size;
				z = prev_height[ordinate];
				color = get_altitude_color(map, z);

				end = duplicate_node(x, y, z, color);
				// draw_algorithm_3(start.x, start.y, end.x, end.y, &canvas, color);
				draw_line(start, end, &canvas, color);

				if (ordinate += 1 == map->width)
				{
					x += cell_size;
					z = prev_height[ordinate + 1];
					color = get_altitude_color(map, z);

					end = duplicate_node(x, y, z, color);

					y += cell_size;
					z = arr_height[ordinate + 1];
					color = get_altitude_color(map, z);
					start = duplicate_node(x, y, z, color);
				if(ordinate != map->width - 1)
					// draw_algorithm_3(start.x, start.y, end.x, end.y, &canvas, color);
					draw_line(start, end, &canvas, color);
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