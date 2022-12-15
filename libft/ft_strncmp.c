/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:23:23 by cboubour          #+#    #+#             */
/*   Updated: 2022/10/24 01:50:44 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	u1;
	unsigned char	u2;

	while (n-- > 0)
	{
		u1 = (unsigned char) *s1;
		u2 = (unsigned char) *s2;
		if (u1 != u2)
			return (u1 - u2);
		if (u1 == '\0')
			return (0);
		s1++;
		s2++;
	}
	return (0);
}
