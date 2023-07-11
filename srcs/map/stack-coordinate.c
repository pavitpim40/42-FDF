/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack-coordinate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:45:11 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/11 19:32:52 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix	*new_element(int x, int y, int z)
{
	t_matrix	*new;

	new = (t_matrix *)malloc(sizeof(t_matrix));
	if (!new)
		terminate(ERR_MAP_INIT);
	new->x = x;
	new->y = y;
	new->z = z;
	new->next = NULL;
	return (new);
}

void	add_head(t_fdf *f, t_matrix *element, t_matrix **matrix_map)
{
	*matrix_map = element;
	f->matrix = matrix_map;
	f->head = *matrix_map;
}

void	add_next(t_matrix *element, t_matrix **matrix_map)
{
	(*matrix_map)->next = element;
	*matrix_map = (*matrix_map)->next;
}

int	list_count(t_matrix *head)
{
	int			count;
	t_matrix	*temp;

	count = 0;
	temp = head;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}
