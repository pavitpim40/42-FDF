/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 02:02:02 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/04 03:38:29 by ppimchan         ###   ########.fr       */
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

t_node create_render_node(t_node t,int color,int altitude, t_map *map)
{

	t_node new_node;
	new_node.x = t.x;
	new_node.y = t.y;
	new_node.z = t.z;
	new_node.color = color;
	new_node.altitude = altitude;
	new_node.percent = (double)(altitude - map->z_min) / map->z_range;
	// iso(&new_node.x, &new_node.y, new_node.z);
	return new_node;
}
