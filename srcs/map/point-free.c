/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point-free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 22:19:31 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/17 02:26:55 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_str_split(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_indeed(char **arr, t_point *point)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	if (point)
		free(point);
}

void	free_all_point(t_point *point)
{
	t_point	*tmp;

	while (point)
	{
		tmp = point->next;
		free(point);
		point = tmp;
	}
}
