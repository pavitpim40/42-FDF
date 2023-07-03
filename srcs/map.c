/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 02:05:22 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/03 23:09:45 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/get_next_line.h"
#include "../libft/libft.h"


t_map *map_init()
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
void print_map(t_map *map, t_coordinate *head)
{

	t_coordinate *temp = head;
	int ordinate = 0;
	while(temp)
	{
		while(ordinate < map->width)
		{
			printf("x : %d, y : %d, z : %d\n", temp->x, temp->y, temp->z);
			temp = temp->next;
			ordinate++;
		}
		ordinate = 0;
		printf("\n");
	}
	

}


void read_map (int fd, t_map *map)
{
	int		axis;
	int		ordinate;
	// int 	altitude;
	char	*axis_string;

	t_coordinate	*coordinate;
	
	char	**axis_array;
	t_coordinate	**coordinate_map;
	t_coordinate	*head;
	

	axis = 0;
	coordinate_map = NULL;
	coordinate = NULL;
	axis_string = get_next_line(fd);
	
	
	while (axis_string)
	{
		axis_array = ft_split(axis_string, ' ');
		ordinate = 0;

		while (axis_array[ordinate])
		{
			int altitude = ft_atoi(axis_array[ordinate]);
			if(axis == 0 && ordinate == 0)
			{
				head = new_coordinate(axis, ordinate, altitude);
				coordinate_map = &head;
				coordinate = head;
			}
			else
			{
				coordinate->next = new_coordinate(axis, ordinate, altitude);
				coordinate = coordinate->next;
			}
			if(altitude < map->z_min)
				map->z_min = altitude;
			if(altitude > map->z_max)
				map->z_max = altitude;	
			ordinate++;
		}
		if(map->width == 0)
		{
			printf("ordinate : %d\n", ordinate);
			map->width = ordinate;
		}
			
		// else if(map->width != ordinate)
		// 	terminate(ERR_MAP_INIT);
		free_split_line(axis_array);
		free(axis_string);
		axis++;
		axis_string = get_next_line(fd);
	}
	map->height = axis;
	map->z_range = map->z_max - map->z_min;
	map->coordinate_map = coordinate_map;

}

