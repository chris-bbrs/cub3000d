/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:26:19 by cboubour          #+#    #+#             */
/*   Updated: 2022/12/18 22:37:20 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_dimensions(t_map *map, int fd)
{
	char	*line;

	map->height = 0;
	line = get_next_line(fd);
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	map->width = ft_strlen(line);
	map->first_map_row = ft_strdup(line);
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

static void	map_array(t_map *map, char *map_name, int fd)
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

static t_bool	check_params_exist(t_map *map)
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

static t_map	*init_map_struct(void)
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

static void	check_dublicate(t_map *map, char **param, char **split)
{
	if (!*param)
		*param = split[1];
	else
		exit_map(map, "Doublicate parameter in map file.");
}

static void	init_fc(t_map *map, char **split, int *arr)
{
	char	**rgb;
	int		i;

	rgb = ft_split(split[1], ',');
	if (ft_2dstrlen(rgb) != 3)
	{
		free(rgb);
		exit_map(map, "Wrong RGB values.");
	}
	i = -1;
	while (++i < 3)
	{
		if (arr[i] == -1)
			arr[i] = ft_atoi(rgb[i]);
		else
		{
			free(rgb);
			exit_map(map, "Doublicate parameter in map file.");
		}
	}
	i = 0;
	while (i < 3 && arr[i] >= 0 && arr[i] <= 255)
		i++;
	if (i != 3)
		return (free(rgb), exit_map(map, "Wrong RGB parameters."));
}

t_map	*initialize_map(char *map_name)
{
	t_map	*map;
	int		fd;
	char	*line;
	char	**split;

	map = init_map_struct();
	fd = open(map_name, O_RDONLY);
	if (fd < 0 || ft_strcmp(map_name + ft_strlen(map_name) - 4, ".cub"))
		rerror("Error\nIncorrect map\n");
	line = get_next_line(fd);
	while (line && !check_params_exist(map))
	{
		split = ft_split(line, ' ');
		if (split[0][0] == 'N' && split[0][1] == 'O')
			check_dublicate(map, &map->no, split);
		if (split[0][0] == 'S' && split[0][1] == 'O')
			check_dublicate(map, &map->so, split);
		if (split[0][0] == 'W' && split[0][1] == 'E')
			check_dublicate(map, &map->we, split);
		if (split[0][0] == 'E' && split[0][1] == 'A')
			check_dublicate(map, &map->ea, split);
		if (split[0][0] == 'F')
			init_fc(map, split, map->f);
		if (split[0][0] == 'C')
			init_fc(map, split, map->c);
		free(line);
		free(split);
		line = get_next_line(fd);
	}
	free(line);
	if (check_params_exist(map))
		map_array(map, map_name, fd);
	else
		exit_map(map, "Invalid map structure");
	check_map(map);
	return (map);
}

// segfualts if tiles are not the last part in the map file
// double param C doesnt work
