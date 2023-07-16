/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point-utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 22:32:00 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/17 02:32:24 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	digit_base(char c, int base)
{
	const char	*digits;
	int			i;

	i = 0;
	digits = "0123456789ABCDEF";
	while (i < base)
	{
		if (digits[i] == ft_toupper(c))
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, int base)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	if (base == 16 || base == 2)
		i += 2;
	else if (base == 8)
		i++;
	else if (base == 10 && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			sign = -1;
	}
	while (str[i] && !ft_whitespace(str[i]))
	{
		result = result * base + digit_base(str[i], base);
		i++;
	}
	return (result * sign);
}
