/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 18:33:53 by cboubour          #+#    #+#             */
/*   Updated: 2023/01/13 15:44:26 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	ch_hor(t_map *map, t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (map->tiles[i])
	{
		j = 0;
		while (map->tiles[i][j] && (map->tiles[i][j] == ' ' || \
			map->tiles[i][j] == '\t'))
			j++;
		if (!map->tiles[i][j] || map->tiles[i][j] != '1')
			exit_map("Left side of map is incorrect");
		while (map->tiles[i][j] && !(map->tiles[i][j] == ' ' || \
			map->tiles[i][j] == '\t'))
			j++;
		if (j < 1 || map->tiles[i][j - 1] != '1')
			exit_map("Right side of map is incorrect");
		i++;
	}
}

static void	ch_ver(t_map *map, t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!map->tiles)
		exit_map("No map found");
	if (!map->tiles[0][0])
		exit_map("No map found");
	while (j < map->width)
	{
		i = 0;
		while (map->tiles[i] && (map->tiles[i][j] == ' ' || \
			map->tiles[i][j] == '\t'))
			i++;
		if (!map->tiles[i] || map->tiles[i][j] != '1')
			exit_map("Top side of map is incorrect");
		while (map->tiles[i] && !(map->tiles[i][j] == ' ' || \
			map->tiles[i][j] == '\t'))
			i++;
		if (i < 1 || map->tiles[i - 1][j] != '1')
			exit_map("Bottom side of map is incorrect");
		j++;
	}
}

static void	ch_tex(t_map *map, t_cub *cub)
{
	int		fd;

	fd = open(map->no, O_RDONLY);
	if (fd < 0)
		exit_map("NO path does not exist");
	if (close(fd) < 0)
		exit_map("Error in closing file");
	fd = open(map->so, O_RDONLY);
	if (fd < 0)
		exit_map("SO path does not exist");
	if (close(fd) < 0)
		exit_map("Error in closing file");
	fd = open(map->we, O_RDONLY);
	if (fd < 0)
		exit_map("WE path does not exist");
	if (close(fd) < 0)
		exit_map("Error in closing file");
	fd = open(map->ea, O_RDONLY);
	if (fd < 0)
		exit_map("EA path does not exist");
	if (close(fd) < 0)
		exit_map("Error in closing file");
}

void	check_map(t_map *map, t_cub *cub)
{
	int		i;
	int		j;
	t_bool	found;

	i = -1;
	found = False;
	while (map->tiles[++i])
	{
		j = -1;
		while (map->tiles[i][++j])
		{
			if (map->tiles[i][j] == 'N' || map->tiles[i][j] == 'S' || \
				map->tiles[i][j] == 'E' || map->tiles[i][j] == 'W')
			{
				if (!found)
					found = True;
				else
					exit_map("Double value in map");
			}
			else if (map->tiles[i][j] != '0' && map->tiles[i][j] != '1' && \
				map->tiles[i][j] != ' ')
				exit_map("Wrong value in map");
		}
	}
	return (ch_hor(map, cub), ch_ver(map, cub), ch_tex(map, cub));
}
