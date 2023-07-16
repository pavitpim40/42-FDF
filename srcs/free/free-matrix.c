/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free-matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:27:09 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/14 16:31:15 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// free metrix
void free_matrix(t_fdf *fdf)
{
	t_matrix	*tmp;

	tmp = fdf->head;
	while (tmp)
	{
		fdf->head = tmp->next;
		free(tmp);
		tmp = fdf->head;
	}
	free(fdf->matrix);
}