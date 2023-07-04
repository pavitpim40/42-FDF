/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:48:49 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/05 02:28:59 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "get_next_line.h"
#include "mlx.h"
#include "libft.h"
#include <limits.h>
#include <errno.h>
#include <stdio.h>


t_fdf *init_mlx_and_window()
{
	t_fdf *fdf;
	fdf = malloc(sizeof(t_fdf));
	if(!fdf)
		terminate("fdf init failed");
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, 1920, 1080, "FDF");
	return (fdf);
}

t_canvas *init_canvas(void *mlx)
{
	t_canvas *canvas;
	
	canvas = malloc(sizeof(t_canvas));
	if(!canvas)
		terminate("canvas init failed");
	canvas->img = mlx_new_image(mlx, 1920, 1080);
	canvas->addr = mlx_get_data_addr(canvas->img, &(canvas->bits_per_pixel), &(canvas->line_length),
									&(canvas->endian));
	return (canvas);
}


// NEED TO Review
void free_fdf(t_fdf *f)
{
	free(f->canvas);
	free(f->map);
	free(f->head);
	free(f->mlx);
	free(f->win);
	free(f);
}

void render_image(t_fdf *f)
{
	mlx_put_image_to_window(f->mlx, f->win, f->canvas->img, 0, 0);
}

int	key_hook(int keycode, t_fdf *f)
{
	// printf("Hello from key_hook!\n");
	printf("keycode: %d\n", keycode);
	// printf("vars->bits_per_pixel: %d\n", vars->bits_per_pixel);
	if (keycode == 53) {
		free_fdf(f);
		exit(0);
	}
	if(keycode == 34) {
		f->camera->projection = ISOMETRIC;
		f->camera->alpha = 0;
		f->camera->beta = 0;
		f->camera->gamma = 0;
		f->camera->x_offset = 0;
		f->camera->y_offset = 0;
		f->canvas = init_canvas(f->mlx);
		
		draw_image(f);
		render_image(f);
		printf("isometric projection\n");
	}
	// P = 35
	if (keycode == 35) {
		f->camera->projection = PARALLEL;
		f->camera->alpha = 0;
		f->camera->beta = 0;
		f->camera->gamma =0;
		f->camera->x_offset = 0;
		f->camera->y_offset = 0;
		f->canvas = init_canvas(f->mlx);
		
		draw_image(f);
		render_image(f);
		
		
		printf("parallel projection\n");
	}
	// right = 124
	if (keycode == 124) {
		f->camera->x_offset += 10;
		f->canvas = init_canvas(f->mlx);
		
		draw_image(f);
		render_image(f);
		printf("right\n");
	}
	// left = 123
	if (keycode == 123) {
		f->camera->x_offset -= 10;
		f->canvas = init_canvas(f->mlx);
		
		draw_image(f);
		render_image(f);
		printf("left\n");
	}

	// up = 126
	if (keycode == 126) {
		f->camera->y_offset -= 10;
		f->canvas = init_canvas(f->mlx);
		
		draw_image(f);
		render_image(f);
		printf("up\n");
	}
	// down = 125
	if (keycode == 125) {
		f->camera->y_offset += 10;
		f->canvas = init_canvas(f->mlx);
		
		draw_image(f);
		render_image(f);
		printf("down\n");
	}

	// rotate-x
	if(keycode == 18) {
		f->camera->alpha += 0.05;
		f->canvas = init_canvas(f->mlx);
		
		draw_image(f);
		render_image(f);
		printf("rotate-x\n");
	}
		if(keycode == 19) {
		f->camera->alpha -= 0.05;
		f->canvas = init_canvas(f->mlx);
		
		draw_image(f);
		render_image(f);
		printf("rotate-x\n");
		
	}

	// rotate-y
	if(keycode == 20) {
		f->camera->beta += 0.05;
		f->canvas = init_canvas(f->mlx);
		
		draw_image(f);
		render_image(f);
		printf("rotate-y\n");
	}
		if(keycode == 21) {
		f->camera->beta -= 0.05;
		f->canvas = init_canvas(f->mlx);
		
		draw_image(f);
		render_image(f);
		printf("rotate-y\n");
	}
	// rotate-z
	if(keycode == 22) {
		f->camera->gamma += 0.05;
		f->canvas = init_canvas(f->mlx);
		
		draw_image(f);
		render_image(f);
		printf("rotate-z\n");
	}
		if(keycode == 23) {
		f->camera->gamma -= 0.05;
		f->canvas = init_canvas(f->mlx);
		
		draw_image(f);
		render_image(f);
		printf("rotate-z\n");
	}
	// zoom in key 24
	if(keycode == 24 || keycode == 69) {
		f->camera->zoom += 1;
		f->canvas = init_canvas(f->mlx);
		
		draw_image(f);
		render_image(f);
		printf("zoom in\n");
	}
	if (keycode == 27|| keycode == 78 ) {
		if(f->camera->zoom > 1)
			f->camera->zoom -= 1;
		f->canvas = init_canvas(f->mlx);
		
		draw_image(f);
		render_image(f);
		printf("zoom out\n");
	}

	// reset R = 15
	if(keycode == 15) {
		f->camera->zoom = cal_min(WIDTH / (f->map->width * 2), HEIGHT / (f->map->height*2));;
		f->camera->alpha = 0;
		f->camera->beta = 0;
		f->camera->gamma = 0;
		f->camera->z_divisor = 1;
		f->camera->x_offset = 0;
		f->camera->y_offset = 0;
		f->camera->projection = ISOMETRIC;
		f->canvas = init_canvas(f->mlx);
		
		draw_image(f);
		render_image(f);
		printf("reset\n");
	}

	return (0);
}

t_camera *init_camera(t_fdf *f)
{
	t_camera *camera;

	camera = malloc(sizeof(t_camera));
	if(!camera)
		terminate("camera init failed");
	camera->zoom = cal_min(WIDTH / (f->map->width * 2), HEIGHT / (f->map->height*2));;
	camera->alpha = 0;
	camera->beta = 0;
	camera->gamma = 0;
	camera->z_divisor = 1;
	camera->x_offset = 0;
	camera->y_offset = 0;
	camera->projection = ISOMETRIC;
	return (camera);
}



int main(int ac, char **av)
{
	t_fdf *f;
	
	if(ac != 2)
		terminate("usage: ./fdf <map>");
	f = init_mlx_and_window();
	f->canvas = init_canvas(f->mlx);
	f->map =  init_map();
	f->head = process_map(av[1],f);
	f->camera = init_camera(f);
	draw_image(f);
	render_image(f);
	mlx_key_hook(f->win, key_hook, f);
	mlx_loop(f->mlx);
	free_fdf(f);
}
