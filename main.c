/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:16:27 by cboubour          #+#    #+#             */
/*   Updated: 2022/12/21 19:38:12 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_map	*map;
	int		i = 0;
	int		j;

	if (argc == 2)
	{
		map = initialize_map(argv[1]);
		printf("NO %s\n", map->no);
		printf("SO %s\n", map->so);
		printf("WE %s\n", map->we);
		printf("EA %s\n", map->ea);
		printf("F %d,%d,%d\n", map->f[0], map->f[1], map->f[2]);
		printf("C %d,%d,%d\n", map->c[0], map->c[1], map->c[2]);
		while (map->tiles[i])
		{
			j = 0;
			while (map->tiles[i][j])
			{
				printf("%c", map->tiles[i][j]);
				j++;
			}
			printf("\n");
			i++;
		}
	}
	else
		printf("Error\nWrong number of arguments.\n");
	exit(EXIT_SUCCESS);
	return (0);
}
