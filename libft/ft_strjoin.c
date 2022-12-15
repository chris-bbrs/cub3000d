/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 18:27:24 by cboubour          #+#    #+#             */
/*   Updated: 2022/04/26 21:46:42 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*conc;
	size_t	len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	conc = (char *)malloc(sizeof(char) * len);
	if (!conc)
		return (NULL);
	ft_memcpy(conc, (char *)s1, ft_strlen((char *)s1) + 1);
	ft_strlcat(conc, s2, len + 1);
	return (conc);
}
