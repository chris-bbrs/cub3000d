/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 22:58:50 by cboubour          #+#    #+#             */
/*   Updated: 2022/12/15 00:13:15 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_map(t_map *to_free, char *str)
{
	int	i;

	if ((*to_free).tiles)
	{
		i = 0;
		while ((*to_free).tiles[i])
		{
			free((*to_free).tiles[i]);
			i++;
		}
	}
	printf("%s", str);
	exit(EXIT_FAILURE);
}

int	rerror(char *str)
{
	printf("%s", str);
	exit(EXIT_FAILURE);
}
