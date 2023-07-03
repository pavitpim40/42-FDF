/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 02:02:02 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/03 18:00:18 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"


// function for duplicate t_node
t_node duplicate_node(int x, int y, int z, int color)
{

	t_node new_node;
	new_node.x = x;
	new_node.y = y;
	new_node.z = z;
	new_node.color = color;
	iso(&new_node.x, &new_node.y, new_node.z);
	return new_node;
}

// function for duplicate t_node
t_node create_render_node(int x, int y,int z,int color,int altitude, t_map *map)
{

	t_node new_node;
	new_node.x = x;
	new_node.y = y;
	new_node.z = z;
	new_node.color = color;
	new_node.altitude = altitude;
	new_node.percent = (double)(altitude - map->z_min) / map->z_range;
	iso(&new_node.x, &new_node.y, new_node.z);
	return new_node;
}

// function for project isometric from node
t_node project_isometric(t_node node)
{
	// isometric angle in alpha beta grammar
	double alpha = 0;
	double beta = 0;
	double gamma = 0;
	rotate_x(&node.y, &node.z, alpha);
	rotate_y(&node.x, &node.z, beta);
	rotate_z(&node.x, &node.y, gamma);
	// printf("node.x , node.y , node.z : (%d, %d, %d)\n", node.x, node.y, node.z);
	iso(&node.x, &node.y, node.z);
	// add offset for x and y
	node.x += WIDTH / 2;
	node.y += 0;
	return node;
}