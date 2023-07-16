/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free-matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:27:09 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 20:35:43 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// free metrix
void	free_matrix(t_fdf *fdf)
{
	t_point	*tmp;

	tmp = fdf->start;
	while (tmp)
	{
		fdf->start = tmp->next;
		free(tmp);
		tmp = fdf->start;
	}
	free(fdf->h_mtx);
	free(fdf->c_mtx);
}
