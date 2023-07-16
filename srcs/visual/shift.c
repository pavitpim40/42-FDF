/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:24:05 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 23:08:15 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	shift_left(t_fdf *f)
{
	f->camera->x_offset -= 10;
	rerender(f);
}

void	shift_rigth(t_fdf *f)
{
	f->camera->x_offset += 10;
	rerender(f);
}

void	shift_up(t_fdf *f)
{
	f->camera->y_offset -= 10;
	rerender(f);
}

void	shift_down(t_fdf *f)
{
	f->camera->y_offset += 10;
	rerender(f);
}
