/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamma.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:39:08 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 13:25:15 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	gamma_increase(t_fdf *f)
{
	f->camera->gamma += 0.05;
	rerender(f);
}

void	gamma_decrease(t_fdf *f)
{
	
		f->camera->gamma -= 0.05;
	rerender(f);
}