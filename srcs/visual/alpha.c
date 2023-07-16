/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alpha.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:36:28 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 23:05:35 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	alpha_increase(t_fdf *f)
{
	f->camera->alpha += 0.05;
	rerender(f);
}

void	alpha_decrease(t_fdf *f)
{
	f->camera->alpha -= 0.05;
	rerender(f);
}
