/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:57:21 by ppimchan          #+#    #+#             */
/*   Updated: 2022/04/14 20:01:04 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	sub_len;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (start < s_len)
		sub_len = s_len - start;
	else
	{
		substr = malloc(sizeof(char) * 1);
		substr[0] = '\0';
		return (substr);
	}
	if (sub_len > len)
		sub_len = len;
	substr = (char *)malloc(sizeof(char) * (sub_len + 1));
	if (substr == 0)
		return (0);
	ft_strlcpy(substr, s + start, sub_len + 1);
	return (substr);
}
