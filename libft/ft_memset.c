/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:46:16 by cboubour          #+#    #+#             */
/*   Updated: 2022/10/20 15:44:54 by dns              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int val, size_t n)
{
	unsigned char	*ptr;

	ptr = dest;
	while (n > 0)
	{
		*ptr = val;
		ptr++;
		n--;
	}
	return (dest);
}
