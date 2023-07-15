/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse-new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 10:24:42 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/15 19:54:31 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	parse_map_new(char *filename)
{
	char	*line;
	// t_list	*head;
	// t_list	*tmp;
	// t_list *new;

	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		terminate(ERR_MAP_INIT);
	

	line = get_next_line(fd);
	char** point_arr = ft_split(line, ' ');
	while(*point_arr)
	{
		printf("point_arr: %s\n", *point_arr);
		t_point *point = new_point(*point_arr);
		printf("point->altitude: %d\n", point->altitude);
		printf("point->color: %x\n\n", point->default_color);
		point_arr++;
	}
	// head =	new_point(line);
	
	// tmp = head;
	// free(line);
	
	// while (line)
	// {
	// 	line = get_next_line(fd);
	// 	if(!line)
	// 		break;
	// 	new = ft_lstnew(line);
	// 	// printf("line: %s\n", line);
	// 	// printf("address of new: %p\n", new);
	// 	tmp->next = new;
	// 	tmp = tmp->next;
	// }
	// printf("before print_list\n\n\n");
	// print_list(head);
}