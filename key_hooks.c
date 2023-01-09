/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:48:24 by gjupy             #+#    #+#             */
/*   Updated: 2023/01/08 22:52:46 by gjupy            ###   ########.fr       */
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

void	my_keyhook(void *param)
{
	t_cub *cub;

	cub = (t_cub *) param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		exit(EXIT_SUCCESS); // change to game_exit_succes
	if ((mlx_is_key_down(cub->mlx, MLX_KEY_W) || mlx_is_key_down(cub->mlx, MLX_KEY_UP)))
		move_up(cub->player, cub->map);
	if ((mlx_is_key_down(cub->mlx, MLX_KEY_S) || mlx_is_key_down(cub->mlx, MLX_KEY_DOWN)))
		move_down(cub->player, cub->map);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		move_left(cub->player, cub->map);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		move_right(cub->player, cub->map);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
	{
		//both camera direction and camera plane must be rotated
      float oldDirX = cub->player->dir_x;
      cub->player->dir_x = cub->player->dir_x * cos(-ROT) - cub->player->dir_y * sin(-ROT);
      cub->player->dir_y = oldDirX * sin(-ROT) + cub->player->dir_y * cos(-ROT);
      double oldPlaneX = cub->player->plane_x;
      cub->player->plane_x = cub->player->plane_x * cos(-ROT) - cub->player->plane_y * sin(-ROT);
      cub->player->plane_y = oldPlaneX * sin(-ROT) + cub->player->plane_y * cos(-ROT);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
	{
	//both camera direction and camera plane must be rotated
      double oldDirX = cub->player->dir_x;
      cub->player->dir_x = cub->player->dir_x * cos(ROT) - cub->player->dir_y * sin(ROT);
      cub->player->dir_y = oldDirX * sin(ROT) + cub->player->dir_y * cos(ROT);
      double oldPlaneX = cub->player->plane_x;
      cub->player->plane_x = cub->player->plane_x * cos(ROT) - cub->player->plane_y * sin(ROT);
      cub->player->plane_y = oldPlaneX * sin(ROT) + cub->player->plane_y * cos(ROT);
	}
	raycast(cub);
}
