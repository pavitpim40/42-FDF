/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:30:26 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 02:28:47 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf	*init_mlx_and_window(void)
{
	t_fdf	*fdf;

	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		terminate("fdf init failed");
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FDF");
	fdf->add_status = 0;
	fdf->camera = NULL;
	return (fdf);
}

t_canvas	*init_canvas(void *mlx)
{
	t_canvas	*canvas;

	canvas = malloc(sizeof(t_canvas));
	if (!canvas)
	{
		free_fdf(mlx);
		terminate("canvas init failed");
	}
	canvas->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	canvas->addr = mlx_get_data_addr(canvas->img, &(canvas->bbp), \
		&(canvas->line_length), &(canvas->endian));
	return (canvas);
}
