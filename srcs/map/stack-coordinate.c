/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack-coordinate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:45:11 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/11 19:05:34 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


// void	stack_coordinate(int axis, int ordinate, int altitude, t_coordinate **coordinate_map)
// {
// 	if (axis == 0 && ordinate == 0)
// 		add_head(f, new_coordinate(axis, ordinate, altitude), coordinate_map);
// 	else
// 		add_next(new_coordinate(axis, ordinate, altitude), coordinate_map);
// }

t_coordinate	*new_coordinate(int x, int y, int z)
{
	t_coordinate	*new;

	new = (t_coordinate *)malloc(sizeof(t_coordinate));
	if (!new)
		terminate(ERR_MAP_INIT);
	new->x = x;
	new->y = y;
	new->z = z;
	new->next = NULL;
	return (new);
}




void	add_head(t_fdf *f, t_coordinate *coordinate, t_coordinate **coordinate_map)
{
	*coordinate_map = coordinate;
	f->coordinate_map = coordinate_map;
	f->head = *coordinate_map;
}

void	add_next(t_coordinate *coordinate, t_coordinate **coordinate_map)
{
	(*coordinate_map)->next = coordinate;
	*coordinate_map = (*coordinate_map)->next;
}

int	list_count(t_coordinate *head)
{
	int				count;
	t_coordinate	*temp;

	count = 0;
	temp = head;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}