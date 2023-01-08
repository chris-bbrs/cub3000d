/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:48:24 by gjupy             #+#    #+#             */
/*   Updated: 2023/01/08 22:02:18 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_right(t_player *player, t_map *map)
{
	float	x;
	float	y;

	x = player->pos_x + player->dir_y * MOV;
	y = player->pos_y - player->dir_x * MOV;
	if (map->tiles[(int) y][(int) x] == '0')
	{
		player->pos_x = x;
		player->pos_y = y;
	}
}

void	move_left(t_player *player, t_map *map)
{
	float	x;
	float	y;

	x = player->pos_x - player->dir_y * MOV;
	y = player->pos_y + player->dir_x * MOV;
	if (map->tiles[(int) y][(int) x] == '0')
	{
		player->pos_x = x;
		player->pos_y = y;
	}
}

void	move_up(t_player *player, t_map *map)
{
	float	y;
	float	x;

	x = player->pos_x + player->dir_x * MOV;
	y = player->pos_y + player->dir_y * MOV;
	if (map->tiles[(int) y][(int) x] == '0')
	{
		player->pos_x = x;
		player->pos_y = y;
	}
}

void	move_down(t_player *player, t_map *map)
{
	float	y;
	float	x;

	x = player->pos_x - player->dir_x * MOV;
	y = player->pos_y - player->dir_y * MOV;
	if (map->tiles[(int) y][(int) x] == '0')
	{
		player->pos_x = x;
		player->pos_y = y;
	}
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_cub *cub;

	cub = (t_cub *) param;
	draw_black(cub);
	raycast(cub);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		exit(EXIT_SUCCESS); // change to game_exit_succes
	if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP) && keydata.action == MLX_REPEAT)
		move_up(cub->player, cub->map);
	if ((keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN) && keydata.action == MLX_REPEAT)
		move_down(cub->player, cub->map);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_REPEAT)
		move_left(cub->player, cub->map);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_REPEAT)
		move_right(cub->player, cub->map);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_REPEAT)
	{
		//both camera direction and camera plane must be rotated
      float oldDirX = cub->player->dir_x;
      cub->player->dir_x = cub->player->dir_x * cos(-ROT) - cub->player->dir_y * sin(-ROT);
      cub->player->dir_y = oldDirX * sin(-ROT) + cub->player->dir_y * cos(-ROT);
      double oldPlaneX = cub->player->plane_x;
      cub->player->plane_x = cub->player->plane_x * cos(-ROT) - cub->player->plane_y * sin(-ROT);
      cub->player->plane_y = oldPlaneX * sin(-ROT) + cub->player->plane_y * cos(-ROT);
	}
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_REPEAT)
	{
	//both camera direction and camera plane must be rotated
      double oldDirX = cub->player->dir_x;
      cub->player->dir_x = cub->player->dir_x * cos(ROT) - cub->player->dir_y * sin(ROT);
      cub->player->dir_y = oldDirX * sin(ROT) + cub->player->dir_y * cos(ROT);
      double oldPlaneX = cub->player->plane_x;
      cub->player->plane_x = cub->player->plane_x * cos(ROT) - cub->player->plane_y * sin(ROT);
      cub->player->plane_y = oldPlaneX * sin(ROT) + cub->player->plane_y * cos(ROT);
	}
}
