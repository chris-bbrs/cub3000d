/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 20:54:37 by cboubour          #+#    #+#             */
/*   Updated: 2022/12/18 21:05:51 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char **s1, char const *s2)
{
	char	*conc;
	size_t	len;

	if (s2 == NULL)
		return (NULL);
	if (!*s1)
		return (ft_strdup(s2));
	len = ft_strlen((char *)*s1) + ft_strlen((char *)s2) + 1;
	conc = (char *)malloc(sizeof(char) * len);
	if (!conc)
		return (NULL);
	ft_memcpy(conc, (char *)*s1, ft_strlen((char *)*s1));
	ft_memcpy(conc + ft_strlen((char *)*s1), s2, ft_strlen((char *)s2));
	conc[len - 1] = '\0';
	free(*s1);
	return (conc);
}
