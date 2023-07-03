/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:48:49 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/04 01:28:40 by ppimchan         ###   ########.fr       */
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

int main(int ac, char **av)
{
	t_fdf *f;
	
	if(ac != 2)
		terminate("usage: ./fdf <map>");
	f = init_mlx_and_window();
	f->canvas = init_canvas(f->mlx);
	f->map =  init_map();
	f->head = read_map(av[1],f);
	draw_image(f);
	render_image(f);
	mlx_loop(f->mlx);
	free_fdf(f);
}
