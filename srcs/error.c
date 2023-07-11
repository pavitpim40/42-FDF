/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:42:24 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/11 16:33:32 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

void	terminate(char *msg)
{
	if (errno == 0)
		ft_putendl_fd(msg, 2);
	else
		perror(msg);
	exit(EXIT_FAILURE);
}
