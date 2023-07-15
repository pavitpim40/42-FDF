/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:48:49 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 05:23:43 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "get_next_line.h"
#include "libft.h"
#include <limits.h>
#include <errno.h>
#include <stdio.h>



void	render_image(t_fdf *f)
{
	// printf("render image\n");
	// printf("f->mlx = %p\n", f->mlx);
	// printf("f->win = %p\n", f->win);
	mlx_put_image_to_window(f->mlx, f->win, f->canvas->img, 0, 0);
}

t_camera	*init_camera(t_fdf *f)
{
	t_camera	*camera;

	camera = malloc(sizeof(t_camera));
	if (!camera)
		terminate("camera init failed");
	// printf("WIDTH: %d\n", WIDTH);
	// printf("HEIGHT: %d\n", HEIGHT);
	// printf("MAP WIDTH: %d\n", f->map->width);
	// printf("MAP HEIGHT: %d\n", f->map->height);
	camera->zoom = cal_min(WIDTH / (f->map->width * 2), \
		HEIGHT / (f->map->height * 2));
	// camera->zoom *= 2;
	camera->alpha = 0;
	camera->beta = 0;
	camera->gamma = 0;
	camera->z_divisor = 5;
	camera->x_offset = 0;
	camera->y_offset = 0;
	camera->projection = ISOMETRIC;
	return (camera);
}

int	main(int ac, char **av)
{
	t_fdf	*f;

	if (ac != 2 || !isFDF(av[1]))
		terminate("usage: ./fdf <map>.fdf");
	f = init_mlx_and_window();
	f->canvas = init_canvas(f->mlx);
	f->map = init_map();
	
	
	// f->head = parse_map(av[1], f);
	parse_map_new(av[1], f);
	f->camera = init_camera(f);
	create_matrix(f);

	draw_image_new(f);
	// draw_image(f);
	render_image(f);
	printf("z_min: %d\n", f->map->z_min);
	printf("z_max: %d\n", f->map->z_max);
	printf("width: %d\n", f->map->width);
	printf("height: %d\n", f->map->height);
	mlx_key_hook(f->win, key_hook, f);
	mlx_mouse_hook(f->win, mouse_hook, f);
	mlx_hook(f->win, 4, 0, mouse_press, f);
	mlx_hook(f->win, 5, 0, mouse_release, f);
	mlx_hook(f->win, 6, 0, mouse_move, f);
	mlx_loop(f->mlx);
	// free_fdf(f);
}
