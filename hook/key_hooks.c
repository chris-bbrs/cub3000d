/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:48:24 by gjupy             #+#    #+#             */
/*   Updated: 2023/01/13 15:36:01 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	movement(t_cub *cub)
{
	if ((mlx_is_key_down(cub->mlx, MLX_KEY_W)
			|| mlx_is_key_down(cub->mlx, MLX_KEY_UP)))
		move_up(cub->player, cub->map, cub->pid);
	else if ((mlx_is_key_down(cub->mlx, MLX_KEY_S)
			|| mlx_is_key_down(cub->mlx, MLX_KEY_DOWN)))
		move_down(cub->player, cub->map, cub->pid);
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		move_left(cub->player, cub->map, cub->pid);
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		move_right(cub->player, cub->map, cub->pid);
	else
		mlx_stop_sound(cub->pid[1]);
}

void	rotation(t_cub *cub)
{
	if ((mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT)
			|| (cub->mouse->tmp_x > S_WIDTH / 2)
			&& !mlx_is_key_down(cub->mlx, MLX_KEY_TAB)))
		rotate_right(cub->player);
	if ((mlx_is_key_down(cub->mlx, MLX_KEY_LEFT)
			|| (cub->mouse->tmp_x < S_WIDTH / 2)
			&& !mlx_is_key_down(cub->mlx, MLX_KEY_TAB)))
		rotate_left(cub->player);
}

void	normal_mov(t_cub *cub)
{
	movement(cub);
	rotation(cub);
	mlx_get_mouse_pos(cub->mlx, &cub->mouse->tmp_x, &cub->mouse->tmp_y);
}

void	run(t_cub *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT_SHIFT))
		cub->player->is_running = true;
	else
	{
		cub->player->is_running = false;
		mlx_stop_sound(cub->pid[2]);
	}
}

void	my_keyhook(void *param)
{
	t_cub	*cub;

	cub = (t_cub *) param;
	cub->player->movespeed = 0.05;
	mouse_rotation(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		exit_game_success(cub);
	if (is_trip_start(cub))
		reverse_mov(cub);
	else
		normal_mov(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_M))
		mlx_stop_sound(cub->pid[0]);
	run(cub);
	raycast(cub);
}
