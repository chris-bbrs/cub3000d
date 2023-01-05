/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:48:24 by gjupy             #+#    #+#             */
/*   Updated: 2023/01/04 18:47:01 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// pos + dir * MOV

void	move_right(t_player *player, t_map *map)
{
	float	x;

	x = player->pos_x + player->dir_x * MOV;
	if (map->tiles[(int) x][(int) player->pos_y] == '0')
		player->pos_x = x;
}

void	move_left(t_player *player, t_map *map)
{
	float	x;

	x = player->pos_x - player->dir_x * MOV;
	if (map->tiles[(int) x][(int) player->pos_y] == '0')
		player->pos_x = x;
}

void	move_up(t_player *player, t_map *map)
{
	float	y;

	y = player->pos_y + player->dir_y * MOV;
	if (map->tiles[(int) player->pos_x][(int) y] == '0')
		player->pos_y = y;
}

void	move_down(t_player *player, t_map *map)
{
	float	y;

	y = player->pos_y - player->dir_y * MOV;
	if (map->tiles[(int) player->pos_x][(int) y] == '0')
		player->pos_y = y;
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_cub *cub;

	cub = (t_cub *) param;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		move_up(cub->player, cub->map);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move_down(cub->player, cub->map);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move_left(cub->player, cub->map);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move_right(cub->player, cub->map);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		exit(EXIT_SUCCESS); // change to game_exit_succes
}
