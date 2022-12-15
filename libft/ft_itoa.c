/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 18:53:33 by cboubour          #+#    #+#             */
/*   Updated: 2022/04/07 21:01:35 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	convert(char *s, long num);
int		count_length(int num);
void	my_reverse(char *s, int len);

char	*ft_itoa(int n)
{
	char	*str;
	int		cnt;
	long	num;

	num = (long)n;
	cnt = 0;
	if (num < 0)
	{
		num = -num;
		cnt++;
	}
	cnt = cnt + count_length(num);
	if (num == 0)
		return (ft_strdup("0"));
	str = malloc(sizeof(char) * (cnt + 1));
	if (!str)
		return (NULL);
	convert(str, num);
	if (cnt > count_length(num))
		str[cnt - 1] = '-';
	str[cnt] = '\0';
	my_reverse(str, cnt);
	return (str);
}

void	convert(char *s, long num)
{
	while (num != 0)
	{
		*s++ = (num % 10) + '0';
		num = num / 10;
	}
}

int	count_length(int num)
{
	int	count;

	count = 0;
	while (num != 0)
	{
		num = num / 10;
		count++;
	}
	return (count);
}

void	my_reverse(char s[], int len)
{
	int		start;
	int		end;
	char	temp;

	start = 0;
	end = len - 1;
	while (start < end)
	{
		temp = s[start];
		s[start] = s[end];
		s[end] = temp;
		start++;
		end--;
	}
}
