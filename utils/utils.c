/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:04:06 by gjupy             #+#    #+#             */
/*   Updated: 2023/01/13 15:34:56 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// pid_t	get_pid(char *s)
// {
// 	FILE	*fn;
// 	pid_t	pid;
// 	size_t	n;
// 	int		ps_fd;
// 	char	*buff;
// 	int		tmp_fd;

// 	tmp_fd = dup(STDOUT_FILENO);
// 	pid = 0;
// 	buff = NULL;
// 	ps_fd = open("ps", O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 	dup2(ps_fd, STDOUT_FILENO);
// 	system("ps");
// 	dup2(tmp_fd, STDOUT_FILENO);
// 	close(tmp_fd);
// 	close(ps_fd);
// 	n = 0;
// 	fn = fopen("ps", "r");
// 	while (getline(&buff, &n, fn) >= 0)
// 	{
// 		if (buff && ft_strnstr(buff, s, ft_strlen(buff)) != NULL)
// 		{
// 			pid = atoi(ft_substr(buff, 0, 10));
// 			break ;
// 		}
// 	}
// 	return (pid);
// }

void	play_walk_sound(t_player *player, pid_t *pid, bool run)
{
	if (run && player->is_running)
	{
		mlx_stop_sound(pid[1]);
		mlx_start_sound(pid[2], "afplay ./textures/horse_fast.mp3 &");
		pid[2] = mlx_get_pid("./textures/horse_fast.mp3");
	}
	else
	{
		mlx_start_sound(pid[1], "afplay ./textures/horse_slow.mp3 &");
		pid[1] = mlx_get_pid("./textures/horse_slow.mp3");
	}
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
	if ((mlx_is_key_down(cub->mlx, MLX_KEY_W)
			|| mlx_is_key_down(cub->mlx, MLX_KEY_UP)))
		rotate_right(cub->player);
	else if ((mlx_is_key_down(cub->mlx, MLX_KEY_S)
			|| mlx_is_key_down(cub->mlx, MLX_KEY_DOWN)))
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

time_t	get_time(void)
{
	struct timeval	time;
	time_t			ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000;
	ms += time.tv_usec / 1000;
	return (ms);
}
