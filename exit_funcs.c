/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 22:58:50 by cboubour          #+#    #+#             */
/*   Updated: 2023/01/04 15:54:23 by gjupy            ###   ########.fr       */
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

// void	exit_game_success(t_game *game)
// {
// 	mlx_close_window(game->window.mlx);
// 	mlx_delete_image(game->window.mlx, game->window.image);
// 	mlx_terminate(game->window.mlx);
// 	free_strings(&game->map, game->height);
// 	exit(EXIT_SUCCESS);
// }
