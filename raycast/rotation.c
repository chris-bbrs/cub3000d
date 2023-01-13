/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 22:01:49 by gjupy             #+#    #+#             */
/*   Updated: 2023/01/13 15:35:25 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
both camera direction and camera plane are rotated
*/
void	rotate_right(t_player *player)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(-ROT) - player->dir_y * sin(-ROT);
	player->dir_y = old_dir_x * sin(-ROT) + player->dir_y * cos(-ROT);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(-ROT) - player->plane_y * sin(-ROT);
	player->plane_y = old_plane_x * sin(-ROT) + player->plane_y * cos(-ROT);
}

/*
both camera direction and camera plane are rotated
*/
void	rotate_left(t_player *player)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(ROT) - player->dir_y * sin(ROT);
	player->dir_y = old_dir_x * sin(ROT) + player->dir_y * cos(ROT);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(ROT) - player->plane_y * sin(ROT);
	player->plane_y = old_plane_x * sin(ROT) + player->plane_y * cos(ROT);
}

void	mouse_rotation(t_cub *cub)
{
	if (!mlx_is_key_down(cub->mlx, MLX_KEY_TAB))
	{
		mlx_set_cursor_mode(cub->mlx, MLX_MOUSE_HIDDEN);
		if (cub->mouse->x > S_WIDTH / 2 || cub->mouse->x < S_WIDTH / 2
			|| cub->mouse->y > S_HEIGHT / 2 || cub->mouse->y < S_HEIGHT / 2)
			mlx_set_mouse_pos(cub->mlx, S_WIDTH / 2, S_HEIGHT / 2);
		mlx_get_mouse_pos(cub->mlx, &cub->mouse->x, &cub->mouse->y);
	}
	else
		mlx_set_cursor_mode(cub->mlx, MLX_MOUSE_NORMAL);
}
