/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:37:23 by gjupy             #+#    #+#             */
/*   Updated: 2023/01/13 15:35:53 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	else
		return (false);
}

void	set_ns(t_player *player, char c)
{
	if (c == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = -PLANE;
		player->plane_y = 0;
	}
	else if (c == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = PLANE;
		player->plane_y = 0;
	}
}

void	set_ew(t_player *player, char c)
{
	if (c == 'E')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = PLANE;
	}
	else if (c == 'W')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -PLANE;
	}
}

void	set_player_pos_dir(t_player *player, int x, int y, char c)
{
	player->pos_x = x + 0.5;
	player->pos_y = y + 0.5;
	set_ns(player, c);
	set_ew(player, c);
}

void	set_player(t_cub *cub)
{
	int	x;
	int	y;

	y = 0;
	while (cub->map->tiles[y])
	{
		x = 0;
		while ((cub->map->tiles[y][x]))
		{
			if (is_player(cub->map->tiles[y][x]))
			{
				set_player_pos_dir(cub->player, x, y, cub->map->tiles[y][x]);
				cub->map->tiles[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}
