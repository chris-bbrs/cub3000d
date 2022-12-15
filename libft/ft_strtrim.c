/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 21:24:36 by cboubour          #+#    #+#             */
/*   Updated: 2022/04/17 22:16:20 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;
	char	*trimed;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = (char *)s1;
	while (ft_strchr(set, *start) && *start != '\0')
		start++;
	if (*start == '\0')
		return (ft_calloc(1, sizeof(char)));
	end = start + ft_strlen(start) - 1;
	while (end > start && ft_strchr(set, *end))
		end--;
	trimed = (char *)malloc(sizeof(char) * ((end + 1) - start + 1));
	if (!trimed)
		return (NULL);
	ft_memcpy(trimed, start, ((end + 1) - start));
	trimed[end - start + 1] = '\0';
	return (trimed);
}
