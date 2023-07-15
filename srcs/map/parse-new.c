/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse-new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 10:24:42 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/15 18:54:27 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// void print_list(t_list *head)
// {
// 	t_list *tmp;
	

// 	tmp = head;
// 	while (tmp)
// 	{
// 		printf("content %s", (char *)tmp->content);
// 		tmp = tmp->next;
// 	}
// }

int ft_atoi_base(char *str, int base)
{
	int i;
	int sign;
	int result;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
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
	int altitude;
	int default_color;
	

	point = (t_point *)malloc(sizeof(t_point));
	if (!point)
		terminate("ERR_POINT_INIT");
	point_arr = ft_split(point_str, ',');
	
	// checkpoint arr size
	altitude = ft_atoi(point_arr[0]);
	if(ft_isdigit(altitude))
		point->altitude = altitude;
	else
		terminate("ERR_POINT_INIT");
	if (point_arr[1])
	{
		default_color = ft_atoi_base(point_arr[1], 16);
		if(ft_isdigit(default_color))
			point->default_color = default_color;
		else
			terminate("ERR_POINT_INIT");
	}

	return (point);
}
void	parse_map_new(char *filename)
{
	char	*line;
	t_list	*head;
	t_list	*tmp;
	t_list *new;

	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		terminate(ERR_MAP_INIT);
	

	line = get_next_line(fd);
	ft_split(line, ' ');
	head =	ft_lstnew(line);
	
	tmp = head;
	// free(line);
	
	while (line)
	{
		line = get_next_line(fd);
		if(!line)
			break;
		new = ft_lstnew(line);
		// printf("line: %s\n", line);
		// printf("address of new: %p\n", new);
		tmp->next = new;
		tmp = tmp->next;
	}
	// printf("before print_list\n\n\n");
	print_list(head);
}