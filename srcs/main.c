/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:48:49 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/04 00:53:03 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "get_next_line.h"
#include "mlx.h"
#include "libft.h"
#include <limits.h>
#include <errno.h>
#include <stdio.h>


t_fdf * fdf_int()
{
	t_fdf *fdf;
	fdf = malloc(sizeof(t_fdf));
	if(!fdf)
		terminate("fdf init failed");
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, 1920, 1080, "FDF");
	return (fdf);
}

t_canvas *image_int(t_fdf *f)
{
	t_canvas *canvas;
	
	canvas = malloc(sizeof(t_canvas));
	if(!canvas)
		terminate("canvas init failed");
	canvas->img = mlx_new_image(f->mlx, 1920, 1080);
	canvas->addr = mlx_get_data_addr(canvas->img, &(canvas->bits_per_pixel), &(canvas->line_length),
									&(canvas->endian));
	printf("canvas->img : %p\n", canvas->img);
	printf("canvas->addr : %p\n", canvas->addr);
	printf("canvas->bits_per_pixel : %d\n", canvas->bits_per_pixel);
	printf("canvas->line_length : %d\n", canvas->line_length);
	printf("canvas->endian : %d\n", canvas->endian);
	
	return (canvas);
}

int main(int ac, char **av)
{
	t_fdf *f;
	t_coordinate *head;
	
	if(ac != 2)
		terminate("usage: ./fdf <map>");
	// Init
	f = fdf_int();
	f->canvas = image_int(f);
	f->map =  map_init();

	// parse map
	read_map(av[1], f->map);
	head = *f->map->coordinate_map;
	// print_map(map, head);


	draw_image(f->map, head, f->canvas);

	mlx_put_image_to_window(f->mlx, f->win, f->canvas->img, 0, 0);
	mlx_loop(f->mlx);
}

// 	while (y_start < y_end)