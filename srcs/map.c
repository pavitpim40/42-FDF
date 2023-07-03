/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 02:05:22 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/04 02:40:10 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/get_next_line.h"
#include "../libft/libft.h"

int list_count(t_coordinate *head)
{
	int count = 0;
	t_coordinate *temp = head;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

// less than 25 lines
t_map *init_map()
{
	t_map *map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		terminate(ERR_MAP_INIT);
	ft_bzero(map, sizeof(t_map));
	map->width = 0;
	map->height = 0;
	map->cell_size = 0;
	map->coordinate_map = NULL;
	map->z_min = INT_MAX;
	map->z_max = INT_MIN;
	map->z_range = 0;
	return (map);
}

// less than 25 lines
t_coordinate *new_coordinate(int x, int y, int z)
{
	t_coordinate *new;

	new = (t_coordinate *)malloc(sizeof(t_coordinate));
	if (!new)
		terminate(ERR_MAP_INIT);
	new->x = x;
	new->y = y;
	new->z = z;
	new->next = NULL;

	return new;
}

// less than 25 lines
void free_split_line(char **split_line)
{
	int i;

	i = 0;
	while (split_line[i])
	{
		free(split_line[i]);
		i++;
	}
	free(split_line);
}

// less than 25 lines
void print_map(t_map *map, t_coordinate *head)
{

	t_coordinate *temp = head;
	int ordinate = 0;
	while (temp)
	{
		while (ordinate < map->width)
		{
			printf("x : %d, y : %d, z : %d\n", temp->x, temp->y, temp->z);
			temp = temp->next;
			ordinate++;
		}
		ordinate = 0;
		printf("\n");
	}
}

void update_altitude(t_fdf *f, int altitude)
{
	if (altitude < f->map->z_min)
		f->map->z_min = altitude;
	if (altitude > f->map->z_max)
		f->map->z_max = altitude;
}

void add_head(t_fdf *f, t_coordinate *coordinate,t_coordinate **coordinate_map)
{
	*coordinate_map = coordinate;
	f->coordinate_map = coordinate_map;
	f->head = *coordinate_map;
}

void add_next(t_coordinate *coordinate, t_coordinate **coordinate_map)
{
	(*coordinate_map)->next = coordinate;
	*coordinate_map = (*coordinate_map)->next;
}

void extract_line(char *axis_string, t_fdf *f, int axis,t_coordinate **coordinate_map)
{
	char **axis_array;
	int ordinate;
	int altitude;

	axis_array = ft_split(axis_string, ' ');
	ordinate = 0;
	while (axis_array[ordinate])
	{
		altitude = ft_atoi(axis_array[ordinate]);
		if (axis == 0 && ordinate == 0)
			add_head(f, new_coordinate(axis, ordinate, altitude), coordinate_map);
		else
			add_next(new_coordinate(axis, ordinate, altitude), coordinate_map);
		update_altitude(f, altitude);
		ordinate++;
	}
	if (f->map->width == 0)
		f->map->width = ordinate;
	else if(f->map->width != ordinate)
		terminate(ERR_MAP_INIT);
	free_split_line(axis_array);
	free(axis_string);
}

void parse_map(int fd, t_fdf *f)
{
	t_coordinate 	**coordinate;
	
	coordinate = malloc(sizeof(t_coordinate *));
	if (!coordinate)
		terminate(ERR_MAP_INIT);

	char *axis_string;
	int axis = 0;
	axis_string = get_next_line(fd);
	while (axis_string)
	{
		extract_line(axis_string,f, axis, coordinate);
		axis++;
		axis_string = get_next_line(fd);
	}
	f->map->height = axis;
	f->map->z_range = f->map->z_max - f->map->z_min;
	printf("list count : %d\n", list_count(f->head));
}

t_coordinate *process_map(char *filename, t_fdf *f)
{
	int				fd;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		terminate(ERR_MAP_INIT);
	parse_map(fd, f);
	close(fd);
	return (f->head);
}
