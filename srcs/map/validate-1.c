/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate-1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 18:50:39 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 19:28:56 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_whitespace(char c)
{
	if(c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_isprefix(char *str, int base)
{
	if (base == 16 && str[0] == '0' && str[1] == 'x')
		return (1);
	if (base == 8 && str[0] == '0')
		return (1);
	if (base == 2 && str[0] == '0' && (str[1] == 'b' || str[1] == 'B'))
		return (1);
	return (0);
}

int	ft_isdigit_base(char c, int base)
{
	char	*digits;
	int		i;

	digits = "0123456789ABCDEF";
	i = 0;
	while (i < base)
	{
		if (digits[i] == ft_toupper(c))
			return (1);
		i++;
	}
	return (0);
}

int	ft_isnum_base(char *str, int base)
{
	int i;
	
	i = 0;
	while(ft_whitespace(str[i]))
		i++;
	if(base != 10 && !ft_isprefix(&str[i], base))
		return (0);
	if (base == 2 || base == 16)
		i += 2;
	else if (base == 8)
		i++;
	else if (base == 10 && (str[i] == '-' || str[i] == '+'))
		i++;
	while (str[i] && !ft_whitespace(str[i]))
	{
		if (!ft_isdigit_base(str[i], base))
			return (0);
		i++;
	}
	return (1);
}