/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:26:19 by cboubour          #+#    #+#             */
/*   Updated: 2023/01/11 22:05:13 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

char	*file_loop(char *line, t_map *map, int fd)
{
	char	**split;

	while (line)
	{
		split = ft_split(line, ' ');
		if (split[0][0] == 'N' && split[0][1] == 'O')
			check_dublicate(map, &map->no, split);
		else if (split[0][0] == 'S' && split[0][1] == 'O')
			check_dublicate(map, &map->so, split);
		else if (split[0][0] == 'W' && split[0][1] == 'E')
			check_dublicate(map, &map->we, split);
		else if (split[0][0] == 'E' && split[0][1] == 'A')
			check_dublicate(map, &map->ea, split);
		else if (split[0][0] == 'F')
			init_fc(map, split, map->f);
		else if (split[0][0] == 'C')
			init_fc(map, split, map->c);
		else if (line[0] != '\n')
			return (free(split), line);
		free(line);
		free(split);
		line = get_next_line(fd);
	}
	return (line);
}

t_map	*initialize_map(char *map_name)
{
	t_map	*map;
	int		fd;
	char	*line;

	map = init_map_struct();
	fd = open(map_name, O_RDONLY);
	if (fd < 0 || ft_strcmp(map_name + ft_strlen(map_name) - 4, ".cub"))
		rerror("Error\nIncorrect map\n");
	line = get_next_line(fd);
	line = file_loop(line, map, fd);
	if (check_params_exist(map))
	{
		map->first_map_row = line;
		map_array(map, map_name, fd);
	}
	else
	{
		free(line);
		exit_map(map, "Invalid map structure");
	}
	check_map(map);
	return (map);
}
