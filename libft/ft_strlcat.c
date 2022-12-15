/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:39:01 by cboubour          #+#    #+#             */
/*   Updated: 2022/04/17 19:58:44 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen((char *)src) + ft_strlen(dst);
	if (ft_strlen((char *)dst) >= dstsize)
		return (ft_strlen((char *)src) + dstsize);
	while (*dst != '\0')
	{
		dst++;
		i++;
	}
	while (i + 1 < dstsize && *src != '\0')
	{
		*dst = *src;
		dst++;
		src++;
		i++;
	}
	*dst = '\0';
	return (len);
}
