/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 21:36:12 by cboubour          #+#    #+#             */
/*   Updated: 2023/01/13 15:44:46 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	get_dimensions(t_map *map, int fd)
{
	char	*line;

	map->height = 1;
	line = get_next_line(fd);
	if (line)
		map->width = ft_strlen(line);
	else
		exit_map("Map not found");
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

void	map_array(t_map *map, t_cub *cub, char *map_name, int fd)
{
	int		i;
	char	*line;

	get_dimensions(map, fd);
	map->tiles = malloc(sizeof(char *) * (map->height + 1));
	if (!map->tiles)
		exit(EXIT_FAILURE);
	if (close(fd) < 0)
		exit_map("Error in closing file");
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		exit_map("Error\nMap not found");
	line = get_next_line(fd);
	while (line && ft_strcmp(line, map->first_map_row))
	{
		free(line);
		line = get_next_line(fd);
	}
	create_arr(line, map, fd);
	if (close(fd) < 0)
		exit_map("Error in closing file");
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
	map->tiles = NULL;
	while (i < 3)
	{
		map->f[i] = -1;
		map->c[i] = -1;
		i++;
	}
	return (map);
}
