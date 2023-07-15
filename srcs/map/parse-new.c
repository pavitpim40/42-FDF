/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse-new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 10:24:42 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/15 23:20:03 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void parse_map_new(char *filename, t_fdf *f)
{
	char *line;

	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		terminate(ERR_MAP_INIT);

	int count = 0;
	int row = 1;
	t_point *head;
	t_point *current;

	line = get_next_line(fd);
	while (line)
	{
		char **point_arr = ft_split(line, ' ');
		int width = 0;
		while (*point_arr)
		{
			t_point *point = new_point(*point_arr);
			if(!point)
				free_all_point(head);
			if (count == 0)
				head = point;
			else
			{
				// printf("address: %p\n", current);
				current->next = point;
			}
			current = point;
			free(*point_arr);
			point_arr++;
			count++;
			width++;
		}
		free(line);
		// if(point_arr)
		// 	free(point_arr);
		// free(point_arr);
		if(row == 1)
			f->map->width = width;
		else if (width != f->map->width)
		{
			free_all_point(head);
			terminate("Invalid map");
		}
		line = get_next_line(fd);
		row++;
	}

	f->start = head;
	print_all_point(head);
}