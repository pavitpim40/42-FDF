/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:06:44 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 04:56:58 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int	mouse_move(int x, int y, t_fdf *f)
{
	// printf("x: %d\n", x);

	// printf("y: %d\n", y);

	// printf("Hello from mouse_move!\n");
	if(f->camera->is_press == 1) {
		// printf("change angle\n");
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

		// draw_image(f);
		rerender(f);
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
		
		// draw_image(f);
		rerender(f);
		// printf("zoom in\n");
	}
	if(button == 4) {
		if(f->camera->zoom > 1)
			f->camera->zoom -= 1;
		f->canvas = init_canvas(f->mlx);
		
		// draw_image(f);
		rerender(f);
		// printf("zoom out\n");
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
		
		// draw_image(f);
		rerender(f);
		// printf("zoom in\n");
	}
	if(button == 4) {
		if(f->camera->zoom > 1)
			f->camera->zoom -= 1;
		f->canvas = init_canvas(f->mlx);
		
		// draw_image(f);
		rerender(f);
		// printf("zoom out\n");
	}
	return (0);
}