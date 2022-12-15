/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 23:23:29 by cboubour          #+#    #+#             */
/*   Updated: 2022/03/31 00:45:46 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	len;

	len = ft_strlen((char *)s1) + 1;
	s2 = (char *)malloc(sizeof(char) * len);
	if (!s2)
		return (NULL);
	ft_memcpy(s2, s1, len);
	return (s2);
}
