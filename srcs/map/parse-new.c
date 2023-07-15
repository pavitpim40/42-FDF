/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse-new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 10:24:42 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/15 20:24:28 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	parse_map_new(char *filename)
{
	char	*line;
	// t_list	*head;
	// t_list	*tmp;
	// t_list *new;

	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		terminate(ERR_MAP_INIT);
	
	int count = 0;
	t_point *head;
	t_point *current;

	line = get_next_line(fd);
	char** point_arr = ft_split(line, ' ');
	// int cin = 1;
	while(*point_arr)
	{
		printf("count: %d\n", count);
		t_point *point = new_point(*point_arr);
		if(count == 0)
		{
			head = point;
		}
		else
		{
			printf("address: %p\n", current);
			current->next = point;
		}
			current = point;

		// printf("point->altitude: %d\n", point->altitude);
		// printf("point->color: %x\n\n", point->default_color);
		point_arr++;
		count++;
	}

	// print from head
	int c = 1;
	while(head)
	{
		printf("point %d\n", c++);
		printf("head->altitude: %d\n", head->altitude);
		printf("head->color: %x\n", head->default_color);
		printf("next: %p\n\n", head->next);
		if(head->next)
			head = head->next;
		else
			break;
	}
}