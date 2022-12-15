/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 22:52:40 by cboubour          #+#    #+#             */
/*   Updated: 2022/04/20 23:04:02 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *c)
{
	int	value;
	int	sign;

	value = 0;
	sign = 1;
	while (*c == ' ' || *c == '\f' || *c == '\n'
		|| *c == '\r' || *c == '\t' || *c == '\v')
	{
		if (*c == '\0')
			return (0);
		c++;
	}
	if (*c == '+' || *c == '-')
	{
		if (*c == '-')
			sign = -1;
		c++;
	}
	while (ft_isdigit(*c))
	{
		value = value * 10;
		value = value + (int)(*c - '0');
		c++;
	}
	return (value * sign);
}
