/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:16:32 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/15 20:03:30 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int ft_atoi_base(char *str, int base)
{
	int i;
	int sign;
	int result;

	i = 0;
	sign = 1;
	result = 0;
	// if (str[i] == '-')
	// {
	// 	sign = -1;
	// 	i++;
	// }
	if(base == 16 || base == 2)
		i += 2;
	else if(base == 8)
		i++;
	else if (base == 10 && (str[i] == '-' || str[i] == '+'))
	{
		if(str[i] == '-')
			sign = -1;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		result = result * base + str[i] - '0';
		i++;
	}
	return (result * sign);
}


t_point *new_point(char *point_str)
{
	t_point *point;
	char **point_arr;
	

	point = (t_point *)malloc(sizeof(t_point));
	if (!point)
		terminate("ERR_POINT_INIT-1");
	point_arr = ft_split(point_str, ',');
	
	// checkpoint arr size
	
	// For altitude
	if(ft_isnum_base(point_arr[0], 10))
		point->altitude = ft_atoi(point_arr[0]);
	else
		terminate("ERR_POINT_INIT-2");

	// For Color
	// printf("point_arr[1]: %s\n", point_arr[1]);
	if (point_arr[1] && !ft_isnum_base(point_arr[1], 16))
		terminate("ERR_POINT_INIT-3");
	if (point_arr[1])
	{
		// printf("inside :point_arr[1]: %s\n", point_arr[1]);
		// printf("inside :point_arr[1]: %x\n", ft_atoi_base(point_arr[1], 16));
		// printf("inside :point_arr[1]: %d\n", ft_atoi_base(point_arr[1], 16));
		// printf("0x810202: %x\n", 0x810202);
		// printf("0x810202: %d\n", 0x810202);
		point->default_color = ft_atoi_base(point_arr[1], 16);
	}	
	else
		point->default_color = -1;
	

	return (point);
}