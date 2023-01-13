/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 21:58:27 by gjupy             #+#    #+#             */
/*   Updated: 2023/01/13 15:35:04 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_right(t_player *player, t_map *map, pid_t *pid)
{
	float	x;
	float	y;

	if (player->is_running == true)
		player->movespeed = 0.15;
	x = player->pos_x + player->dir_y * player->movespeed;
	y = player->pos_y - player->dir_x * player->movespeed;
	if (map->tiles[(int) y][(int) x] == '0')
	{
		play_walk_sound(player, pid, true);
		player->pos_x = x;
		player->pos_y = y;
	}
}

void	move_left(t_player *player, t_map *map, pid_t *pid)
{
	float	x;
	float	y;

	if (player->is_running == true)
		player->movespeed = 0.15;
	x = player->pos_x - player->dir_y * player->movespeed;
	y = player->pos_y + player->dir_x * player->movespeed;
	if (map->tiles[(int) y][(int) x] == '0')
	{
		play_walk_sound(player, pid, true);
		player->pos_x = x;
		player->pos_y = y;
	}
}

void	move_up(t_player *player, t_map *map, pid_t *pid)
{
	float	y;
	float	x;

	if (player->is_running == true)
		player->movespeed = 0.1;
	x = player->pos_x + player->dir_x * player->movespeed;
	y = player->pos_y + player->dir_y * player->movespeed;
	if (map->tiles[(int) y][(int) x] == '0')
	{
		play_walk_sound(player, pid, true);
		player->pos_x = x;
		player->pos_y = y;
	}
}

void	move_down(t_player *player, t_map *map, pid_t *pid)
{
	float	y;
	float	x;

	x = player->pos_x - player->dir_x * player->movespeed;
	y = player->pos_y - player->dir_y * player->movespeed;
	if (map->tiles[(int) y][(int) x] == '0')
	{
		play_walk_sound(player, pid, false);
		player->pos_x = x;
		player->pos_y = y;
	}
}
