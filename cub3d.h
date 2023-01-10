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

# include "MLX42/include/MLX42/MLX42.h"
# include "Get_next_line/get_next_line.h"
# include "./libft/libft.h"
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

# define S_WIDTH 1600
# define S_HEIGHT 920
# define PLANE 1.66
# define MOV 0.06
# define ROT 0.06
# define FOV 60.0 // Field of view in degrees
# define NUM_RAYS 360 // Number of rays to cast
# define RAY_ANGLE FOV / NUM_RAYS // Angle between each ray

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
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
	mlx_image_t		*b_img;
	mlx_image_t		*player;
}	t_img;

typedef struct s_ray{
	float	camera;
	float	dir_x;
	float	dir_y;
	float	sideDist_x;
	float	sideDist_y;
	float	deltaDist_x;
	float	deltaDist_y;
	float	wallDist;
	int		side;
	int		step_x;
	int		step_y;
	int		pos_x;
	int		pos_y;
}	t_ray;

typedef struct s_draw_wall
{
	int	lineHeight;
	int	drawStart;
	int	drawEnd;
}	t_draw_wall;

typedef struct s_texture
{
	mlx_texture_t	**tex;
	int				tex_x;
	int				tex_y;
}	t_tex;

typedef struct s_game_structs
{
	t_map		*map;
	mlx_t		*mlx;
 	t_player	*player;
	t_img		*img;
	t_ray		*ray;
	t_draw_wall	*draw_wall;
	t_tex		*tex;
	time_t		start_time;
	pid_t		pid[2];
}	t_cub;

void	exit_game_success(t_cub *cub);

time_t	get_time(void);
pid_t	get_pid(char *s);

void	my_keyhook(void *param);
void	set_player(t_cub *cub);
void	raycast(t_cub *cub);
void	draw_bg(t_cub *cub, int raycount);

t_map		*initialize_map(char *map);
void		exit_map(t_map *to_free, char *str);
int			rerror(char *str);
void		check_map(t_map *map);
void		initialize(t_cub *cub);

#endif
