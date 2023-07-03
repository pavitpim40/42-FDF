/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 02:02:02 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/03 05:07:21 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void rotate_x(int *y, int *z, double alpha)
{
	int previous_y;

	previous_y = *y;
	*y = previous_y * cos(alpha) + *z * sin(alpha);
	*z = -previous_y * sin(alpha) + *z * cos(alpha);
}

static void rotate_y(int *x, int *z, double beta)
{
	int previous_x;

	previous_x = *x;
	*x = previous_x * cos(beta) + *z * sin(beta);
	*z = -previous_x * sin(beta) + *z * cos(beta);
}

static void rotate_z(int *x, int *y, double gamma)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(gamma) - previous_y * sin(gamma);
	*y = previous_x * sin(gamma) + previous_y * cos(gamma);
}

// function for iso
void iso(int *x, int *y, int z)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
}

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