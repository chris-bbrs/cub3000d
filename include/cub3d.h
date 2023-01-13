/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 00:14:45 by cboubour          #+#    #+#             */
/*   Updated: 2022/12/13 00:14:45 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../Get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <memory.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <signal.h>

# define S_WIDTH 1920
# define S_HEIGHT 1080
# define PLANE 1.66
# define ROT 0.06

typedef enum e_bool
{
	True = 1,
	False = 0
}	t_bool;

typedef struct s_map_details
{
	size_t	width;
	size_t	height;
	char	*first_map_row;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f[3];
	int		c[3];
	char	**tiles;
}	t_map;

typedef struct s_player{
	bool	is_running;
	float	pos_x;
	float	pos_y;
	float	dir_x;
	float	dir_y;
	float	player_x;
	float	player_y;
	float	plane_x;
	float	plane_y;
	float	angle;
	float	fov;
	int		ver_dir;
	int		hor_dir;
	float	movespeed;
	int		turndir;
	float	turnspeed;
	float	dist_proj_plane;
}	t_player;

typedef struct s_images{
	mlx_image_t		*b_img;
	mlx_image_t		*player;
}	t_img;

typedef struct s_ray{
	float	camera;
	float	dir_x;
	float	dir_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	wall_dist;
	int		side;
	int		step_x;
	int		step_y;
	int		pos_x;
	int		pos_y;
}	t_ray;

typedef struct s_draw_wall
{
	int	line_height;
	int	draw_start;
	int	draw_end;
}	t_draw_wall;

typedef struct s_texture
{
	mlx_texture_t	**tex;
	int				tex_x;
	int				tex_y;
}	t_tex;

typedef struct s_mouse
{
	int	x;
	int	y;
	int	tmp_x;
	int	tmp_y;
}	t_mouse;

typedef struct s_game_structs
{
	t_map		*map;
	mlx_t		*mlx;
	t_player	*player;
	t_img		*img;
	t_ray		*ray;
	t_draw_wall	*draw_wall;
	t_tex		*tex;
	t_mouse		*mouse;
	time_t		start_time;
	pid_t		pid[3];
	int			potential_side_x;
	int			potential_side_y;
	int			wall_direction;
}	t_cub;

void	initialize(t_cub *cub);

void	play_walk_sound(t_player *player, pid_t *pid, bool run);
bool	is_trip_start(t_cub *cub);
void	reverse_mov(t_cub *cub);
time_t	get_time(void);

void	rotate_right(t_player *player);
void	rotate_left(t_player *player);
void	mouse_rotation(t_cub *cub);

void	move_right(t_player *player, t_map *map, pid_t *pid);
void	move_left(t_player *player, t_map *map, pid_t *pid);
void	move_up(t_player *player, t_map *map, pid_t *pid);
void	move_down(t_player *player, t_map *map, pid_t *pid);

void	my_keyhook(void *param);
void	set_player(t_cub *cub);
void	raycast(t_cub *cub);
void	draw_bg(t_cub *cub, int raycount);

void	check_map(t_map *map, t_cub *cub);
t_map	*initialize_map(t_cub *cub, char *map_name);

void	exit_map(char *str);
void	exit_game_success(t_cub *cub);
int		rerror(char *str);

void	map_array(t_map *map, t_cub *cub, char *map_name, int fd);
t_bool	check_params_exist(t_map *map);
t_map	*init_map_struct(void);

void	dda(t_cub *cub);
void	draw_bg(t_cub *cub, int raycount);
void	draw_vertical_line(t_cub *cub, int raycount);

void	free_strings(char ***s);

#endif
