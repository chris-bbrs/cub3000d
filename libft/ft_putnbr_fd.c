/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 22:44:20 by cboubour          #+#    #+#             */
/*   Updated: 2022/04/08 00:47:27 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	rec_print(long num, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	long	num;

	num = (long)n;
	if (num < 0)
	{
		num = -num;
		write(fd, "-", 1);
	}
	if (num == 0)
		write(fd, "0", 1);
	else
		rec_print(num, fd);
}

void	rec_print(long number, int fd)
{
	char	c;

	c = (number % 10) + '0';
	number = number / 10;
	if (number != 0)
		rec_print(number, fd);
	write(fd, &c, 1);
}
