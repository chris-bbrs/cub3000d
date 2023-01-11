/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 22:58:50 by cboubour          #+#    #+#             */
/*   Updated: 2023/01/10 20:41:57 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_strings(char ***s)
{
	int	i;

	i = 0;
	while ((*s)[i])
	{
		free((*s)[i]);
		i++;
	}
	free(*s);
}

void	free_structs(t_cub *cub)
{
	mlx_texture_t	***tmp;

	free(cub->player);
	free(cub->ray);
	free(cub->draw_wall);
	tmp = &cub->tex->tex;
	free(*tmp);
	free(cub->tex);
	free(cub->img);
}

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

void	exit_game_success(t_cub *cub)
{
	if (cub->pid[0])
		kill(cub->pid[0], SIGKILL);
	mlx_close_window(cub->mlx);
	mlx_delete_image(cub->mlx, cub->img->b_img);
	mlx_delete_image(cub->mlx, cub->img->player);
	mlx_terminate(cub->mlx);
	free_strings(&cub->map->tiles);
	free_structs(cub);
	exit(EXIT_SUCCESS);
}
