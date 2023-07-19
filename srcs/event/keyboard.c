/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:17:11 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/19 15:07:32 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	key_projection(int keycode, t_fdf *f)
{
	if (keycode == 34)
		isometric_projection(f);
	if (keycode == 35)
		topview_projection(f);
}

void	key_offset(int keycode, t_fdf *f)
{
	if (keycode == 124)
		shift_rigth(f);
	else if (keycode == 123)
		shift_left(f);
	else if (keycode == 126)
		shift_up(f);
	else if (keycode == 125)
		shift_down(f);
}

void	key_rotate(int keycode, t_fdf *f)
{
	if (keycode == 18) 
		alpha_increase(f);
	else if (keycode == 19)
		alpha_decrease(f);
	else if (keycode == 20) 
		beta_increase(f);
	else if (keycode == 21)
		beta_decrease(f);
	else if (keycode == 22) 
		gamma_increase(f);
	else if (keycode == 23)
		gamma_decrease(f);
}

void	key_altitude(int keycode, t_fdf *f)
{
	if (keycode == 43)
	{
		f->camera->z_divisor += 0.1;
		rerender(f);
	}
	else if (keycode == 47)
	{
		if (f->camera->z_divisor > 0.3)
			f->camera->z_divisor -= 0.1;
		rerender(f);
	}
}

int	key_hook(int keycode, t_fdf *f)
{
	if (keycode == 53)
	{
		free_fdf(f);
		exit(0);
	}
	else if (keycode >= 18 && keycode <= 23)
		key_rotate(keycode, f);
	else if (keycode == 34 || keycode == 35)
		key_projection(keycode, f);
	else if (keycode == 43 || keycode == 47)
		key_altitude(keycode, f);
	else if (keycode >= 123 && keycode <= 126)
		key_offset(keycode, f);
	else if (keycode == 24 || keycode == 69)
		zoom_in(f);
	else if (keycode == 27 || keycode == 78)
		zoom_out(f);
	else if (keycode == 15)
		reset(f);
	return (0);
}
