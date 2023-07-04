/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 02:02:02 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/04 17:31:38 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"




// function for duplicate t_node
// t_node create_render_node(int x, int y,int z,int color,int altitude, t_map *map)
// {

// 	t_node new_node;
// 	new_node.x = x;
// 	new_node.y = y;
// 	new_node.z = z;
// 	new_node.color = color;
// 	new_node.altitude = altitude;
// 	new_node.percent = (double)(altitude - map->z_min) / map->z_range;
// 	iso(&new_node.x, &new_node.y, new_node.z);
// 	return new_node;
// }

t_node create_render_node(t_node t,int color,int altitude, t_map *map, char *name)
{

	t_node new_node;
	printf("name: %s\n", name);
	printf("<- x:%d y:%d z:%d \n",t.x,t.y,t.z);
	new_node.x = t.x;
	new_node.y = t.y;
	new_node.z = t.z;
	new_node.color = color;
	new_node.altitude = altitude;
	new_node.percent = (double)(altitude - map->z_min) / map->z_range;
	iso(&new_node.x, &new_node.y, new_node.z);
	printf("-> x:%d y:%d z:%d \n\n",new_node.x,new_node.y,new_node.z);
	return new_node;
}

t_node create_project_node(int axis,int ordinate,int altitude, int color,t_map *map)
{
	// cal zoom level
	t_node new_node;


	int zoom_level = 1;
	zoom_level  = cal_min(WIDTH / (map->width * 2), HEIGHT / (map->height*2));

	// printf("zoom_level: %d\n", zoom_level);
	// printf("axis: %d\n", axis);
	// printf("ordinate: %d\n", ordinate);
	// printf("altitude: %d\n", altitude);

	// cal x,y,z
	int x = ordinate * zoom_level;
	int y = axis * zoom_level;
	// int z = altitude * zoom_level;
	// printf("altitude: %d\n", altitude);

	x -= (map->width * zoom_level) / 2;
	y -= (map->height * zoom_level) / 2;

	new_node.x = x;
	new_node.y = y;
	new_node.z = altitude * zoom_level /5;
	new_node.color = color;
		iso(&new_node.x, &new_node.y, new_node.z);
	new_node.x+= WIDTH / 2;
	new_node.y+=  100+HEIGHT / 2;
	new_node.altitude = altitude;
	
	// printf("z = %d\n", new_node.z);
	// printf("\n");
	return (new_node);

	

}

