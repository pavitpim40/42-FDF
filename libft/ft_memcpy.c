/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 02:34:51 by ppimchan          #+#    #+#             */
/*   Updated: 2022/04/10 11:39:32 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void	*dst, const void *src, size_t n)
{
	size_t		i;
	char		*content_dst;
	char		*content_src;

	if (!dst && !src)
		return (0);
	content_dst = (char *)dst;
	content_src = (char *)src;
	i = 0;
	while (i < n)
	{
		content_dst[i] = content_src[i];
		i++;
	}
	return (dst);
}
