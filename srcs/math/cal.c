/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 01:58:12 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 05:18:24 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	cal_abs(int x, int y)
{
	if (y > x)
		return (y - x);
	else
		return (x - y);
}

int	cal_max(int x, int y)
{
	if (x > y)
		return (x);
	else
		return (y);
}

int	cal_min(int x, int y)
{
	if (x < y)
		return (x);
	else
		return (y);
}

int	cal_avg(int start, int end, double percentage)
{
	return ((int)((percentage) * start + (1 - percentage) * end));
}
