/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 18:33:53 by cboubour          #+#    #+#             */
/*   Updated: 2022/12/18 22:26:42 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_horizontal(t_map *map)
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
			exit_map(map, "Left side of map is incorrect");
		while (map->tiles[i][j] && !(map->tiles[i][j] == ' ' || \
			map->tiles[i][j] == '\t'))
			j++;
		if (j < 1 || map->tiles[i][j - 1] != '1')
			exit_map(map, "Right side of map is incorrect");
		i++;
	}
}

static void	check_vertical(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!map->tiles)
		exit_map(map, "Not map found");
	if (!map->tiles[0][0])
		exit_map(map, "Not map found");
	while (j < map->width)
	{
		i = 0;
		while (map->tiles[i] && (map->tiles[i][j] == ' ' || \
			map->tiles[i][j] == '\t'))
			i++;
		if (!map->tiles[i] || map->tiles[i][j] != '1')
			exit_map(map, "Top side of map is incorrect");
		while (map->tiles[i] && !(map->tiles[i][j] == ' ' || \
			map->tiles[i][j] == '\t'))
			i++;
		if (i < 1 || map->tiles[i - 1][j] != '1')
			exit_map(map, "Bottom side of map is incorrect");
		j++;
	}
}

static void	check_texture(t_map *map)
{
	int		fd;

	fd = open(map->no, O_RDONLY);
	if (fd < 0)
		exit_map(map, "NO path does not exist");
	if (close(fd) < 0)
		exit_map(map, "Error in closing file\n");
	fd = open(map->so, O_RDONLY);
	if (fd < 0)
		exit_map(map, "SO path does not exist");
	if (close(fd) < 0)
		exit_map(map, "Error in closing file\n");
	fd = open(map->we, O_RDONLY);
	if (fd < 0)
		exit_map(map, "WE path does not exist");
	if (close(fd) < 0)
		exit_map(map, "Error in closing file\n");
	fd = open(map->ea, O_RDONLY);
	if (fd < 0)
		exit_map(map, "EA path does not exist");
	if (close(fd) < 0)
		exit_map(map, "Error in closing file\n");
}

void	check_map(t_map *map)
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
					exit_map(map, "Double value in map");
			}
			else if (map->tiles[i][j] != '0' && map->tiles[i][j] != '1' && \
				map->tiles[i][j] != ' ')
				exit_map(map, "Wrong value in map");
		}
	}
	return (check_horizontal(map), check_vertical(map), check_texture(map));
}
