/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 21:36:12 by cboubour          #+#    #+#             */
/*   Updated: 2023/01/11 21:36:58 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_dimensions(t_map *map, int fd)
{
	char	*line;

	map->height = 1;
	line = get_next_line(fd);
	map->width = ft_strlen(line);
	while (line)
	{
		map->height++;
		free(line);
		line = get_next_line(fd);
		if (line && ft_strlen(line) > map->width)
			map->width = ft_strlen(line);
	}
	if (line)
		free(line);
}

static void	create_arr(char *line, t_map *map, int fd)
{
	int	i;

	i = 0;
	while (ft_strlen(line) < map->width)
		line = ft_strjoin_free(&line, " ");
	map->tiles[i] = line;
	while (++i < map->height)
	{
		line = get_next_line(fd);
		while (ft_strlen(line) < map->width)
			line = ft_strjoin_free(&line, " ");
		map->tiles[i] = line;
	}
	map->tiles[i] = NULL;
}

void	map_array(t_map *map, char *map_name, int fd)
{
	int		i;
	char	*line;

	get_dimensions(map, fd);
	map->tiles = malloc(sizeof(char *) * (map->height + 1));
	if (!map->tiles)
		exit(EXIT_FAILURE);
	if (close(fd) < 0)
		exit_map(map, "Error in closing file\n");
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		exit_map(map, "Error\nMap not found\n");
	line = get_next_line(fd);
	while (line && ft_strcmp(line, map->first_map_row))
	{
		free(line);
		line = get_next_line(fd);
	}
	create_arr(line, map, fd);
	if (close(fd) < 0)
		exit_map(map, "Error in closing file\n");
}

t_bool	check_params_exist(t_map *map)
{
	t_bool	all;
	int		i;

	i = 0;
	all = True;
	while (i < 3)
	{
		if (map->f[i] == -1 || map->c[i] == -1)
			all = False;
		else
			all = True;
		i++;
	}
	if (all && map->no && map->so && map->we && map->ea)
		all = True;
	else
		all = False;
	return (all);
}

t_map	*init_map_struct(void)
{
	int		i;
	t_map	*map;

	i = 0;
	map = ft_calloc(1, sizeof(t_map));
	while (i < 3)
	{
		map->f[i] = -1;
		map->c[i] = -1;
		i++;
	}
	return (map);
}
