/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:48:49 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/18 23:53:26 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_camera	*init_camera(t_fdf *f)
{
	t_camera	*camera;

	camera = malloc(sizeof(t_camera));
	if (!camera)
	{
		if (f->start)
			free_all_point(f->start);
		terminate("camera init failed");
	}
	camera->zoom = cal_min(WIDTH / (f->map->width * 2), \
		HEIGHT / (f->map->height * 2));
	camera->alpha = 0;
	camera->beta = 0;
	camera->gamma = 0;
	camera->z_divisor = 5;
	camera->x_offset = 0;
	camera->y_offset = 0;
	camera->projection = ISOMETRIC;
	return (camera);
}

int	close_window(t_fdf *f)
{
	free_fdf(f);
	exit(0);
}

int	main(int ac, char **av)
{
	t_fdf	*f;

	if (ac != 2 || !is_fdf(av[1]) || !is_exist(av[1]))
		terminate("usage: ./fdf <map>.fdf");
	f = init_mlx_and_window();
	f->canvas = init_canvas(f->mlx);
	f->map = init_map(f);
	parse_map(av[1], f);
	f->camera = init_camera(f);
	create_matrix(f);
	draw_image(f);
	render_image(f);
	mlx_hook(f->win, 2, 0, key_hook, f);
	mlx_hook(f->win, 17, 0, close_window, f);
	mlx_hook(f->win, 4, 0, mouse_press, f);
	mlx_hook(f->win, 5, 0, mouse_release, f);
	mlx_hook(f->win, 6, 0, mouse_move, f);
	mlx_loop(f->mlx);
	free_fdf(f);
}
