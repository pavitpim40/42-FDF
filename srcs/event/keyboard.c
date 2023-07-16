/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:17:11 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/14 19:19:14 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"



int	key_hook(int keycode, t_fdf *f)
{
	// printf("keycode: %d\n", keycode);
	if (keycode == 53) {
		free_fdf(f);
		exit(0);
	}
	// 34 = I
	if(keycode == 34)
		isometric_projection(f);
	// 35 = P
	if (keycode == 35)
		topview_projection(f);
	// right = 124
	if (keycode == 124)
		shift_rigth(f);
	// left = 123
	if (keycode == 123)
		shift_left(f);
	// up = 126
	if (keycode == 126)
		shift_up(f);
	// down = 125
	if (keycode == 125)
		shift_down(f);
	// rotate-x
	if(keycode == 18) 
		alpha_increase(f);
	if(keycode == 19)
		alpha_decrease(f);
	// rotate-y
	if(keycode == 20) 
		beta_increase(f);
	if(keycode == 21)
		beta_decrease(f);
	// rotate-z
	if(keycode == 22) 
		gamma_increase(f);
	if(keycode == 23)
		gamma_decrease(f);
	// zoom in key 24
	if(keycode == 24 || keycode == 69)
		zoom_in(f);
	if (keycode == 27|| keycode == 78 )
		zoom_out(f);


	// reset R = 15
	if(keycode == 15)
		reset(f);
	// z_divisor inc 43
	if(keycode == 43) {
		// printf("z_divisor: %f\n", f->camera->z_divisor);
		f->camera->z_divisor += 0.1;
		f->canvas = init_canvas(f->mlx);
		
		draw_image(f);
		render_image(f);
		// printf("z_divisor inc\n");
	}
	// z_divisor dec 47
	if(keycode == 47) {
		if(f->camera->z_divisor > 1)
			f->camera->z_divisor -= 0.1;
		f->canvas = init_canvas(f->mlx);
		
		draw_image(f);
		render_image(f);
		// printf("z_divisor dec\n");
	}

	return (0);
}







