/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:31:13 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/11 22:34:50 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom_in(t_fdf *f)
{
	f->camera->zoom += 1;
	rerender(f);
}
void	zoom_out(t_fdf *f)
{
	if(f->camera->zoom > 1)
		f->camera->zoom -= 1;
	rerender(f);
}