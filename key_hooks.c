/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:48:24 by gjupy             #+#    #+#             */
/*   Updated: 2023/01/11 03:45:44 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

pid_t	get_pid(char *s)
{
	FILE	*fn;
	pid_t	pid;
	size_t	n;
	int		ps_fd;
	char	*buff;
	int		tmp_fd;

	tmp_fd = dup(STDOUT_FILENO);
	pid = 0;
	buff = NULL;
	ps_fd = open("ps", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(ps_fd, STDOUT_FILENO);
	system("ps");
	dup2(tmp_fd, STDOUT_FILENO);
	close(tmp_fd);
	close(ps_fd);
	n = 0;
	fn = fopen("ps", "r");
	while (getline(&buff, &n, fn) >= 0)
	{
		if (buff && ft_strnstr(buff, s, ft_strlen(buff)) != NULL)
		{
			pid = atoi(ft_substr(buff, 0, 10));
			break ;
		}
	}
	return (pid);
}

void	move_right(t_player *player, t_map *map, pid_t *pid)
{
	float	x;
	float	y;

	x = player->pos_x + player->dir_y * MOV;
	y = player->pos_y - player->dir_x * MOV;
	if (map->tiles[(int) y][(int) x] == '0')
	{
		if (!pid[1])
			system("afplay ./textures/horse_slow.mp3 &");
		pid[1] = get_pid("./textures/horse_slow.mp3");
		player->pos_x = x;
		player->pos_y = y;
	}
}

void	move_left(t_player *player, t_map *map, pid_t *pid)
{
	float	x;
	float	y;

	x = player->pos_x - player->dir_y * MOV;
	y = player->pos_y + player->dir_x * MOV;
	if (map->tiles[(int) y][(int) x] == '0')
	{
		if (!pid[1])
			system("afplay ./textures/horse_slow.mp3 &");
		pid[1] = get_pid("./textures/horse_slow.mp3");
		player->pos_x = x;
		player->pos_y = y;
	}
}

void	move_up(t_player *player, t_map *map, pid_t *pid)
{
	float	y;
	float	x;

	x = player->pos_x + player->dir_x * MOV;
	y = player->pos_y + player->dir_y * MOV;
	if (map->tiles[(int) y][(int) x] == '0')
	{
		if (!pid[1])
			system("afplay ./textures/horse_slow.mp3 &");
		pid[1] = get_pid("./textures/horse_slow.mp3");
		player->pos_x = x;
		player->pos_y = y;
	}
}

void	move_down(t_player *player, t_map *map, pid_t *pid)
{
	float	y;
	float	x;

	x = player->pos_x - player->dir_x * MOV;
	y = player->pos_y - player->dir_y * MOV;
	if (map->tiles[(int) y][(int) x] == '0')
	{
		if (!pid[1])
			system("afplay ./textures/horse_slow.mp3 &");
		pid[1] = get_pid("./textures/horse_slow.mp3");
		player->pos_x = x;
		player->pos_y = y;
	}
}

void	rotate_right(t_player *player)
{
	//both camera direction and camera plane must be rotated
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(-ROT) - player->dir_y * sin(-ROT);
	player->dir_y = old_dir_x * sin(-ROT) + player->dir_y * cos(-ROT);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(-ROT) - player->plane_y * sin(-ROT);
	player->plane_y = old_plane_x * sin(-ROT) + player->plane_y * cos(-ROT);
}

void	rotate_left(t_player *player)
{
	//both camera direction and camera plane must be rotated
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(ROT) - player->dir_y * sin(ROT);
	player->dir_y = old_dir_x * sin(ROT) + player->dir_y * cos(ROT);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(ROT) - player->plane_y * sin(ROT);
	player->plane_y = old_plane_x * sin(ROT) + player->plane_y * cos(ROT);
}

bool	is_trip_start(t_cub *cub)
{
	time_t	time;

	time = get_time();
	if ((time - cub->start_time) <= 20000 && time > (cub->start_time + 6000))
		return (true);
	return (false);
}

void	reverse_mov(t_cub *cub)
{
	if ((mlx_is_key_down(cub->mlx, MLX_KEY_W) || mlx_is_key_down(cub->mlx, MLX_KEY_UP)))
		rotate_right(cub->player);
	else if ((mlx_is_key_down(cub->mlx, MLX_KEY_S) || mlx_is_key_down(cub->mlx, MLX_KEY_DOWN)))
		rotate_left(cub->player);
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		move_up(cub->player, cub->map, cub->pid);
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		move_down(cub->player, cub->map, cub->pid);
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		move_left(cub->player, cub->map, cub->pid);
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		move_right(cub->player, cub->map, cub->pid);
	else if (cub->pid[1])
		kill(cub->pid[1], SIGKILL);
	if (cub->pid[0] && mlx_is_key_down(cub->mlx, MLX_KEY_M))
	{
		kill(cub->pid[0], SIGKILL);
		cub->pid[0] = 0;
	}
}

void	my_keyhook(void *param)
{
	t_cub *cub;

	cub = (t_cub *) param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		exit_game_success(cub);
	// if (is_trip_start(cub))
	// 	reverse_mov(cub);
	// else
	// {
		if ((mlx_is_key_down(cub->mlx, MLX_KEY_W) || mlx_is_key_down(cub->mlx, MLX_KEY_UP)))
			move_up(cub->player, cub->map, cub->pid);
		else if ((mlx_is_key_down(cub->mlx, MLX_KEY_S) || mlx_is_key_down(cub->mlx, MLX_KEY_DOWN)))
			move_down(cub->player, cub->map, cub->pid);
		else if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
			move_left(cub->player, cub->map,cub->pid);
		else if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
			move_right(cub->player, cub->map, cub->pid);
		else if (cub->pid[1])
			kill(cub->pid[1], SIGKILL);
		if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
			rotate_right(cub->player);
		if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
			rotate_left(cub->player);
		if (cub->pid[0] && mlx_is_key_down(cub->mlx, MLX_KEY_M))
		{
			kill(cub->pid[0], SIGKILL);
			cub->pid[0] = 0;
		}
	// }
	raycast(cub);
}
