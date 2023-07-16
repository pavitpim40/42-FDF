/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point-create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:16:32 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 23:35:53 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	*new_point(char *point_str)
{
	t_point		*point;
	char		**point_arr;

	point = (t_point *)malloc(sizeof(t_point));
	if (!point)
		return (NULL);
	point_arr = ft_split(point_str, ',');
	if (ft_isnum_base(point_arr[0], 10))
		point->altitude = ft_atoi(point_arr[0]);
	else
	{
		free_indeed(point_arr, point);
		return (NULL);
	}
	if (point_arr[1] && !ft_isnum_base(point_arr[1], 16))
	{
		free_indeed(point_arr, point);
		return (NULL);
	}
	push_color(point, point_arr[1]);
	point->next = NULL;
	free_indeed(point_arr, NULL);
	return (point);
}

void	push_color(t_point *point, char *default_color)
{
	if (default_color)
		point->default_color = ft_atoi_base(default_color, 16);
	else
		point->default_color = -1;
}

void	add_point_back(t_point **head, t_point **current, t_point *new)
{
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
}
