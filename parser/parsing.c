/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:26:19 by cboubour          #+#    #+#             */
/*   Updated: 2023/01/13 15:45:07 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	check_dublicate(t_map *map, t_cub *cub, char **param, char **split)
{
	if (!*param)
		*param = split[1];
	else
		exit_map("Duplicate parameter in map file");
}

static void	free_exit_map(char	**rgb)
{
	free_strings(&rgb);
	exit_map("Wrong RGB values");
}

static void	init_fc(t_map *map, t_cub *cub, char **split, int *arr)
{
	char	**rgb;
	int		i;

	rgb = ft_split(split[1], ',');
	free(split[1]);
	if (ft_2dstrlen(rgb) != 3)
		free_exit_map(rgb);
	i = -1;
	while (++i < 3)
	{
		if (arr[i] == -1)
			arr[i] = ft_atoi(rgb[i]);
		else
			free_exit_map(rgb);
	}
	i = 0;
	while (i < 3 && arr[i] >= 0 && arr[i] <= 255)
		i++;
	if (i != 3)
		return (free_strings(&rgb), exit_map("Wrong RGB parameters"));
	free_strings(&rgb);
}

static char	*file_loop(char *line, t_cub *cub, t_map *map, int fd)
{
	char	**split;

	while (line)
	{
		split = ft_split(line, ' ');
		if (split[0][0] == 'N' && split[0][1] == 'O')
			check_dublicate(map, cub, &map->no, split);
		else if (split[0][0] == 'S' && split[0][1] == 'O')
			check_dublicate(map, cub, &map->so, split);
		else if (split[0][0] == 'W' && split[0][1] == 'E')
			check_dublicate(map, cub, &map->we, split);
		else if (split[0][0] == 'E' && split[0][1] == 'A')
			check_dublicate(map, cub, &map->ea, split);
		else if (split[0][0] == 'F')
			init_fc(map, cub, split, map->f);
		else if (split[0][0] == 'C')
			init_fc(map, cub, split, map->c);
		else if (line[0] != '\n')
			return (free_strings(&split), line);
		free(line);
		free(split[0]);
		free(split);
		line = get_next_line(fd);
	}
	return (line);
}

t_map	*initialize_map(t_cub *cub, char *map_name)
{
	t_map	*map;
	int		fd;
	char	*line;

	fd = open(map_name, O_RDONLY);
	if (fd < 0 || ft_strcmp(map_name + ft_strlen(map_name) - 4, ".cub"))
	{
		close(fd);
		exit_map("Error\nIncorrect map");
	}
	map = init_map_struct();
	line = get_next_line(fd);
	line = file_loop(line, cub, map, fd);
	if (check_params_exist(map))
	{
		map->first_map_row = line;
		map_array(map, cub, map_name, fd);
	}
	else
	{
		free(line);
		exit_map("Invalid map structure");
	}
	check_map(map, cub);
	return (map);
}
