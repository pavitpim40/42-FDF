/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:16:32 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 04:37:21 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


static int		ft_isdigit_base(char c, int base)
{
	const char	*digits = "0123456789ABCDEF";
	int			i;

	i = 0;
	while (i < base)
	{
		if (digits[i] == ft_toupper(c))
			return (i);
		i++;
	}
	return (-1);
}


int ft_atoi_base(char *str, int base)
{
	int i;
	int sign;
	int result;

	i = 0;
	sign = 1;
	result = 0;

	if(base == 16 || base == 2)
		i += 2;
	else if(base == 8)
		i++;
	else if (base == 10 && (str[i] == '-' || str[i] == '+'))
	{
		if(str[i] == '-')
			sign = -1;
	}
	// printf("str_atoi_base: %s\n", str);
	// printf("str[i]: %c\n", str[i]);

	while (str[i] && !ft_whitespace(str[i]))
	{
		// printf("str[i]: %c\n", str[i]);
		// printf("str[i]- '0': %d\n\n", str[i] - '0');
		result = result * base + ft_isdigit_base(str[i], base);
		i++;
	}
	return (result * sign);
}



void print_all_point(t_point *head)
{
	t_point *current;
	int	count; 

	count = 0;
	current = head;
	while (current)
	{
		printf("altitude: %d, color: %x\n", current->altitude, current->default_color);
		current = current->next;
		count++;
	}
	printf("count: %d\n", count);
}
void free_all_point(t_point *point)
{
	t_point	*tmp;
	printf("free_all_point\n");
	printf("point: %p\n", point);
	while (point)
	{
		printf("point: %p\n", point);
		tmp = point->next;
		free(point);
		point = tmp;
	}
}

void free_str_split(char **arr)
{
	size_t i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void free_indeed(char **arr, t_point *point)
{
	size_t i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	if(point)
		free(point);
}

t_point *new_point(char *point_str, t_fdf *f)
{
	t_point *point;
	char **point_arr;
	
	point = (t_point *)malloc(sizeof(t_point));
	if (!point)
		return (NULL);
	point_arr = ft_split(point_str, ',');
	if(ft_isnum_base(point_arr[0], 10))
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
	{
		// printf("point_arr[1]: %s\n", point_arr[1]);
		// printf("atoi_base: %d\n\n", ft_atoi_base(point_arr[1], 16));
		// if(ft_isprefix(point_arr[1], 16))
		// 	point->default_color = ft_atoi_base(point_arr[1], 16);
		// else
		// {
		// 	free_indeed(point_arr, point);
		// 	return (NULL);
		// }
		f->have_default_color = 1;
		point->default_color = ft_atoi_base(point_arr[1], 16);
	}
	else
		point->default_color = -1;
	point->next = NULL;
	free_indeed(point_arr,NULL);
	return (point);
}