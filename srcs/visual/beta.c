/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:39:11 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 23:05:42 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	beta_increase(t_fdf *f)
{
	f->camera->beta += 0.05;
	rerender(f);
}

void	beta_decrease(t_fdf *f)
{
	f->camera->beta -= 0.05;
	rerender(f);
}
