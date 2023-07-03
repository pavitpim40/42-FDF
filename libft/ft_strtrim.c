/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:15:08 by ppimchan          #+#    #+#             */
/*   Updated: 2022/04/14 20:03:30 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*res;

	if (!s1 || !set)
		return (0);
	i = 0;
	len = ft_strlen(s1);
	while (len > 0 && ft_strchr(set, s1[len - 1]) != NULL)
		len--;
	while (len > 0 && ft_strchr(set, s1[i++]) != NULL)
		len--;
	i -= 1;
	res = ft_calloc(len + 1, 1);
	if (!res)
		return (NULL);
	j = 0;
	while (j < len)
		res[j++] = s1[i++];
	res[j] = '\0';
	return (res);
}
