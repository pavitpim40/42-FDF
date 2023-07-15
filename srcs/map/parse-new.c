/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse-new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 10:24:42 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/15 20:32:05 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void parse_map_new(char *filename)
{
	char *line;

	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		terminate(ERR_MAP_INIT);

	int count = 0;
	t_point *head;
	t_point *current;

	line = get_next_line(fd);
	while (line)
	{
		char **point_arr = ft_split(line, ' ');
		
		while (*point_arr)
		{
			t_point *point = new_point(*point_arr);
			if (count == 0)
				head = point;
			else
			{
				printf("address: %p\n", current);
				current->next = point;
			}
			current = point;
			free(*point_arr);
			point_arr++;
			count++;
			
		}
		free(line);
		line = get_next_line(fd);
	}

	// print from head
	int c = 1;
	while (head)
	{
		printf("point %d\n", c++);
		printf("altitude: %d\n", head->altitude);
		printf("color: %x\n", head->default_color);
		printf("next: %p\n\n", head->next);
		if (head->next)
			head = head->next;
		else
			break;
	}
}