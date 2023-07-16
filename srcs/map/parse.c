/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 10:24:42 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 14:14:55 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	update_altitude(t_fdf *f, int altitude)
{
	if (altitude < f->map->z_min)
		f->map->z_min = altitude;
	if (altitude > f->map->z_max)
		f->map->z_max = altitude;
}


int	isFDF(char *filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (extension && ft_strncmp(extension, ".fdf", ft_strlen(extension)) == 0)
		return (1);
	return (0);
}

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
		add_point_back(head,current,point);
		update_altitude(f,point->altitude);
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
	t_point *head;
	t_point *current;
	int	height;

	head = NULL;
	current = NULL;
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		process_line(line,f,&head,&current);
		line = get_next_line(fd);
		height++;
	}
	f->map->height = height;
	
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
	f->map->z_range = f->map->z_max - f->map->z_min;

}
