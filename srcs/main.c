/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:48:49 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/11 16:37:02 by ppimchan         ###   ########.fr       */
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
	canvas->addr = mlx_get_data_addr(canvas->img, &(canvas->bbp), &(canvas->line_length),
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
		f->camera->z_divisor = 3;
		f->camera->x_offset = 0;
		f->camera->y_offset = 0;
		f->camera->projection = ISOMETRIC;
		f->canvas = init_canvas(f->mlx);
		
		draw_image(f);
		render_image(f);
		printf("reset\n");
	}
	// z_divisor inc 43
	if(keycode == 43) {
		printf("z_divisor: %f\n", f->camera->z_divisor);
		f->camera->z_divisor += 0.1;
		f->canvas = init_canvas(f->mlx);
		
		draw_image(f);
		render_image(f);
		printf("z_divisor inc\n");
	}
	// z_divisor dec 47
	if(keycode == 47) {
		if(f->camera->z_divisor > 1)
			f->camera->z_divisor -= 0.1;
		f->canvas = init_canvas(f->mlx);
		
		draw_image(f);
		render_image(f);
		printf("z_divisor dec\n");
	}

	return (0);
}


int mouse_hook(int button, int x, int y, t_fdf *f)
{
	printf("button: %d\n", button);
	printf("x: %d\n", x);
	printf("y: %d\n", y);
	printf("f->camera->zoom: %d\n", f->camera->zoom);
	printf("Hello from mouse_hook!\n");

	if(button == 5) {
		f->camera->zoom += 1;
		f->canvas = init_canvas(f->mlx);
		
		draw_image(f);
		render_image(f);
		printf("zoom in\n");
	}
	if(button == 4) {
		if(f->camera->zoom > 1)
			f->camera->zoom -= 1;
		f->canvas = init_canvas(f->mlx);
		
		draw_image(f);
		render_image(f);
		printf("zoom out\n");
	}
	return (0);
}

int mouse_move(int x, int y, t_fdf *f)
{
	printf("x: %d\n", x);

	printf("y: %d\n", y);

	printf("Hello from mouse_move!\n");
	if(f->camera->is_press == 1) {
		printf("change angle\n");
		int prev_x = f->camera->x;
		// int prev_y = f->camera->y;
	
		f->camera->x = x;
		f->camera->y = y;
		if(x-prev_x >= 0) {
			// f->camera->beta += 0.02;
			f->camera->gamma -= 0.02;
		} else if (x-prev_x < 0) {
			// f->camera->beta -= 0.02;
			f->camera->gamma += 0.02;
		}
	// 	if(y-prev_y > 0) {
	// 		f->camera->alpha += 0.02;
	// 		// f->camera->gamma -= 0.02;
	// 	} else if (y-prev_y < 0) {
	// 		f->camera->alpha -= 0.02;
	// 		// f->camera->gamma += 0.02;
	// 	}
	// 	int cos_alpha = cos(f->camera->alpha)*cos(f->camera->alpha);
	// 	int cos_beta = cos(f->camera->beta)*cos(f->camera->beta);
	// 	int gamma = 1 - cos_alpha - cos_beta;
	// 	gamma = sqrt(gamma);
	// if((x-prev_x )*(y-prev_y) >= 0)
	// 	f->camera->gamma += sqrt(f->camera->gamma);
	// else if((x-prev_x)*(y-prev_y) < 0)
	// 	f->camera->gamma -= sqrt(f->camera->gamma);
	
		f->canvas = init_canvas(f->mlx);

		draw_image(f);
		render_image(f);
	}
	return (0);
}

int mouse_press(int button, int x, int y, t_fdf *f)
{
	printf("button: %d\n", button);
	printf("x: %d\n", x);
	printf("y: %d\n", y);
	printf("f->camera->zoom: %d\n", f->camera->zoom);
	printf("Hello from mouse_press!\n");

	if(button == 5) {
		f->camera->zoom += 1;
		f->canvas = init_canvas(f->mlx);
		
		draw_image(f);
		render_image(f);
		printf("zoom in\n");
	}
	if(button == 4) {
		if(f->camera->zoom > 1)
			f->camera->zoom -= 1;
		f->canvas = init_canvas(f->mlx);
		
		draw_image(f);
		render_image(f);
		printf("zoom out\n");
	}

	if(button == 1) {
		f->camera->is_press = 1;
	}
	return (0);
}

int mouse_release(int button, int x, int y, t_fdf *f)
{
	printf("button: %d\n", button);
	printf("x: %d\n", x);
	printf("y: %d\n", y);
	printf("f->camera->zoom: %d\n", f->camera->zoom);
	printf("Hello from mouse_release!\n");
	f->camera->is_press = 0;
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
	camera->z_divisor = 3;
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
	mlx_mouse_hook(f->win, mouse_hook, f);
	// mouse move

	// mouse press x  =4 
	mlx_hook(f->win, 4, 0, mouse_press, f);
	// mouse release x = 5
	mlx_hook(f->win, 5, 0, mouse_release, f);

		mlx_hook(f->win, 6, 0, mouse_move, f);

	mlx_loop(f->mlx);
	free_fdf(f);
}
