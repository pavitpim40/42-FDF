/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 00:07:47 by ppimchan          #+#    #+#             */
/*   Updated: 2022/03/31 13:52:36 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(long nbr)
{
	int	size;

	size = 0;
	while (nbr >= 10)
	{
		nbr /= 10;
		++size;
	}
	return (size + 1);
}

static int	ft_power(int base, int power)
{
	int	i;
	int	result;

	i = 0;
	result = 1;
	while (i < power)
	{
		result = result * base;
		i++;
	}
	return (result);
}

static char	*ft_write(char *str, long nbr, int sign, int len)
{
	int	i;

	i = 0;
	if (sign < 0)
	{
		str[i++] = '-';
		len-- ;
	}
	while (len--)
	{
		str[i++] = (nbr / ft_power(10, len)) + '0';
		nbr = nbr % ft_power(10, len);
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		sign;
	long	nbr;

	len = 0;
	sign = 1;
	if (n < 0)
	{
		sign = -1;
		len = 1;
	}
	nbr = (long)n * (long)sign;
	len += ft_intlen (nbr);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	return (ft_write(str, nbr, sign, len));
}
