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

# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480

#define FOV 60.0 // Field of view in degrees
#define NUM_RAYS 360 // Number of rays to cast
#define RAY_ANGLE FOV / NUM_RAYS // Angle between each ray

typedef enum e_bool
{
	True = 1,
	False = 0
}	t_bool;

typedef struct map_details
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

typedef struct game_structs
{
	t_map	*map;
	mlx_t	*mlx;
}	t_cub;

t_map		*initialize_map(char *map);
void		exit_map(t_map *to_free, char *str);
int			rerror(char *str);
void		check_map(t_map *map);
#endif
