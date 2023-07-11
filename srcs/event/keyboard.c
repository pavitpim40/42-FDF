/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:17:11 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/11 17:23:48 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_fdf *f)
{
	printf("keycode: %d\n", keycode);
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







