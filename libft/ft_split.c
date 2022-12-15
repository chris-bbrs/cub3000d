/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 01:04:30 by cboubour          #+#    #+#             */
/*   Updated: 2022/07/03 22:42:00 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	my_free(char **arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free (arr);
	return (0);
}

static int	insert_substr(char **ar, char const *str, char c, size_t len)
{
	size_t	i;
	int		cnt;
	int		ar_i;

	i = 0;
	cnt = 0;
	ar_i = 0;
	while (str[i] == c)
		i++;
	while (i <= len)
	{
		if (str[i] != c)
			cnt++;
		else if (str[i - 1] != c)
		{
			ar[ar_i++] = ft_substr(str, i - cnt, cnt);
			if (!ar)
				return (my_free(ar));
			cnt = 0;
		}
		i++;
	}
	ar[ar_i] = NULL;
	return (1);
}

static size_t	words_count(char const *str, char c)
{
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	while (str[i] == c)
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == c && str[i - 1] != c)
			cnt++;
		i++;
	}
	return (cnt);
}

static char	**nulloc(char **arr)
{
	arr = malloc(sizeof(char *));
	arr[0] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**address_ar;
	char	*str;
	char	ch[2];

	if (s == NULL)
		return (NULL);
	address_ar = NULL;
	if (*s == '\0')
		return (nulloc(address_ar));
	ch[0] = c;
	ch[1] = 0;
	str = ft_strjoin(s, ch);
	if (!str)
		return (NULL);
	address_ar = malloc(sizeof(char *) * (words_count(str, c) + 1));
	if (!address_ar)
	{
		free(str);
		return (NULL);
	}
	if (insert_substr(address_ar, str, c, ft_strlen((char *)s)) == 0)
		return (nulloc(address_ar));
	free(str);
	return (address_ar);
}
