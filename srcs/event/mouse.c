/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:06:44 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 19:08:19 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouse_move(int x, int y, t_fdf *f)
{
	int	prev_x;
	int	prev_y;

	prev_x = f->camera->x;
	prev_y = f->camera->y;
	if (f->camera->is_press == 1)
	{
		f->camera->x = x;
		f->camera->y = y;
		if (x - prev_x >= 0)
			f->camera->gamma -= 0.02;
		else if (x - prev_x < 0)
			f->camera->gamma += 0.02;
		if (y - prev_y >= 0)
			f->camera->alpha += 0.02;
		else if (y - prev_y < 0)
			f->camera->alpha -= 0.02;
		rerender(f);
	}
	return (0);
}

int	mouse_press(int button, int x, int y, t_fdf *f)
{
	f->camera->x = x;
	f->camera->y = y;
	if (button == 5)
	{
		f->camera->zoom += 1;
		rerender(f);
	}
	if (button == 4)
	{
		if (f->camera->zoom > 1)
			f->camera->zoom -= 1;
		rerender(f);
	}
	if (button == 1)
		f->camera->is_press = 1;
	return (0);
}

int	mouse_release(int button, int x, int y, t_fdf *f)
{
	f->camera->x = x;
	f->camera->y = y;
	if (button == 1)
		f->camera->is_press = 0;
	return (0);
}
