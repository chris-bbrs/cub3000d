/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 23:08:55 by cboubour          #+#    #+#             */
/*   Updated: 2022/03/29 16:10:11 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		lo;
	int		cnt;

	lo = -1;
	cnt = 0;
	while (*s != '\0')
	{
		if (*s == (char)c)
			lo = cnt;
		cnt++;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	if (lo >= 0)
		return ((char *)(s - cnt + lo));
	return (NULL);
}
