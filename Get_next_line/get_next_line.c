/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 00:40:52 by cboubour          #+#    #+#             */
/*   Updated: 2022/12/14 23:51:55 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strjoin(char **s1, char const *s2)
{
	char	*conc;
	size_t	len;

	if (s2 == NULL)
		return (NULL);
	if (!*s1)
		return (ft_strdup(s2));
	len = ft_strlen2((char *)*s1) + ft_strlen2((char *)s2) + 1;
	conc = (char *)malloc(sizeof(char) * len);
	if (!conc)
		return (NULL);
	ft_memcpy(conc, (char *)*s1, ft_strlen2((char *)*s1));
	ft_memcpy(conc + ft_strlen2((char *)*s1), s2, ft_strlen2((char *)s2));
	conc[len - 1] = '\0';
	free(*s1);
	return (conc);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*line;
	int			sz;

	if (fd < 0)
		return (NULL);
	buff = ft_calloc(2, 1);
	sz = read(fd, buff, 1);
	if (!sz)
	{
		free(buff);
		return (NULL);
	}
	line = ft_strdup(buff);
	while (sz > 0 && buff[0] != '\n')
	{
		sz = read(fd, buff, 1);
		buff[1] = 0;
		if (sz && buff[0] != '\n')
			line = ft_strjoin(&line, buff);
	}
	free(buff);
	return (line);
}
