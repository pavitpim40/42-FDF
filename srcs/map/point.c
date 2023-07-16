/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:16:32 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 19:50:37 by ppimchan         ###   ########.fr       */
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
	if (point_arr[1])
		point->default_color = ft_atoi_base(point_arr[1], 16);
	else
		point->default_color = -1;
	point->next = NULL;
	free_indeed(point_arr, NULL);
	return (point);
}

int	ft_atoi_base(char *str, int base)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	if (base == 16 || base == 2)
		i += 2;
	else if (base == 8)
		i++;
	else if (base == 10 && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			sign = -1;
	}
	while (str[i] && !ft_whitespace(str[i]))
	{
		result = result * base + ft_isdigit_base(str[i], base);
		i++;
	}
	return (result * sign);
}

void	print_all_point(t_point *head)
{
	t_point	*current;
	int		count; 

	count = 0;
	current = head;
	while (current)
	{
		printf("alt:%d,%x\n", current->altitude, current->default_color);
		current = current->next;
		count++;
	}
	printf("count: %d\n", count);
}
