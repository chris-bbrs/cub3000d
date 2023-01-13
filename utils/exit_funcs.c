/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 22:58:50 by cboubour          #+#    #+#             */
/*   Updated: 2023/01/13 16:04:52 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_strings(char ***s)
{
	int	i;

	if (*s)
	{
		i = 0;
		while ((*s)[i])
		{
			free((*s)[i]);
			i++;
		}
		free(*s);
	}
}

void	exit_map(char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

void	exit_game_success(t_cub *cub)
{
	mlx_stop_sound(cub->pid[0]);
	mlx_stop_sound(cub->pid[1]);
	mlx_stop_sound(cub->pid[2]);
	mlx_close_window(cub->mlx);
	mlx_delete_image(cub->mlx, cub->img->b_img);
	mlx_delete_image(cub->mlx, cub->img->player);
	mlx_delete_texture(cub->tex->tex[0]);
	mlx_delete_texture(cub->tex->tex[1]);
	mlx_delete_texture(cub->tex->tex[2]);
	mlx_delete_texture(cub->tex->tex[3]);
	mlx_terminate(cub->mlx);
	exit(EXIT_SUCCESS);
}
