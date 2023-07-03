/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:31:07 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/03 15:56:50 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/fdf.h"
#include "../includes/color.h"
#include "libft.h"


t_node *create_current_node (t_node *start, t_node *end, int x, int y,int prime_k,int dx, int dy, t_map *map)
{	
	int placement; 
	int span;
	double percent;
	t_node *current;

	if(dx > dy) {
		placement =cal_min(start->x,end->x) + prime_k;
		span = cal_abs(start->x,end->x);
		percent = placement / span;
	} else {
		placement = cal_min(start->y,end->y) + prime_k;
		span = cal_abs(start->y,end->y);
		percent = placement / span;
	}

	current = (t_node *)malloc(sizeof(t_node));
	if (!current)
		terminate(ERR_MAP_INIT);
	current->x = x;
	current->y = y;
	current->z = percent *(map->z_range) + map->z_min;
	return(current);

}
int get_altitude_color(t_map *map,int z )
{
	int color;
	double percentage;

	// if (map->z_range == 0)
	// 	return (DEFAULT_COLOR);
	// printf("------------------\n");
	// printf("z : %d\n", z);
	// printf("diff : %d\n", z- map->z_min);
	// printf("z_min : %d\n", map->z_min);
	// printf("z_range : %d\n", map->z_range);

	percentage = (double)(z - map->z_min) / map->z_range;
	if (percentage < 0.2)
		color = COLOR_DISCO;
	else if (percentage < 0.4)
		color = COLOR_BRICK_RED;
	else if (percentage < 0.6)
		color = COLOR_FLAMINGO;
	else if (percentage < 0.8)
		color = COLOR_JAFFA;
	else
		color = COLOR_SAFFRON;
	return (color);
}

static int ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int ft_atoi_base(const char *str, int str_base)
{
	int i;
	int sign;
	int result;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		result = result * str_base + str[i] - '0';
		i++;
	}
	return (result * sign);
}