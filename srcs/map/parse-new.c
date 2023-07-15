/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse-new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 10:24:42 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 00:17:50 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void add_point_back(t_point **head,t_point **current, t_point *new)
{
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
}

void	validate_mapsize(int width,t_fdf *f, t_point *head)
{
	if(!f->map->width)
		f->map->width = width;
	else if (width != f->map->width)
	{
		free_all_point(head);
		terminate("Invalid map");
	}
}
void	process_line(char *line, t_fdf *f,t_point **head,t_point **current)
{
	char **point_arr = ft_split(line, ' ');
	int width = 0;
	while (*point_arr)
	{
		t_point *point = new_point(*point_arr);
		if(!point)
			free_all_point(*head);
		printf("head address: %p\n", *head);
		add_point_back(head,current,point);
		free(*point_arr);
		point_arr++;
		width++;
	}
	free(line);
	validate_mapsize(width,f,*head);
}

t_point *process_map_new(int fd,t_fdf *f)
{
	char *line;
	int row = 1;
	t_point *head;
	t_point *current;

	line = get_next_line(fd);
	head = NULL;
	current = NULL;
	while (line)
	{
		process_line(line,f,&head,&current);
		line = get_next_line(fd);
		row++;
	}
	return head;
}

void parse_map_new(char *filename, t_fdf *f)
{
	
	int fd;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		terminate(ERR_MAP_INIT);
	f->start = process_map_new(fd,f);
	close(fd);
	print_all_point(f->start);
}