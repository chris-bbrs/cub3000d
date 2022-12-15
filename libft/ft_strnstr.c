/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 21:24:04 by cboubour          #+#    #+#             */
/*   Updated: 2022/04/17 20:00:07 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	int		j;
	int		length;
	int		needle_len;

	i = 0;
	j = 0;
	length = (int)len;
	needle_len = ft_strlen((char *)needle);
	if (needle_len == 0)
		return ((char *)haystack);
	if (length < 0)
		len = ft_strlen((char *)haystack);
	while (haystack[i] && i <= (int)(len - needle_len))
	{
		if (ft_strncmp(&haystack[j], needle, needle_len) == 0)
			return ((char *)&haystack[j]);
		j++;
		i++;
	}
	return (NULL);
}
