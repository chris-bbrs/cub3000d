/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:48:41 by cboubour          #+#    #+#             */
/*   Updated: 2023/01/04 19:33:49 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	create_floor_ceil(t_cub *cub)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	f_colour;
	uint32_t	c_colour;

	cub->img->floor = mlx_new_image(cub->mlx, S_WIDTH, S_HEIGHT / 2);
	cub->img->ceil = mlx_new_image(cub->mlx, S_WIDTH, S_HEIGHT / 2);
	f_colour = (cub->map->f[0] << 24) | (cub->map->f[1] << 16);
	f_colour = f_colour | (cub->map->f[2] << 8) | 255;
	c_colour = (cub->map->c[0] << 24) | (cub->map->c[1] << 16);
	c_colour = c_colour | (cub->map->c[2]  << 8) | 255;
	i = 0;
	while (i <= S_HEIGHT / 2)
	{
		j = 0;
		while (j <= S_WIDTH)
		{
			mlx_put_pixel(cub->img->floor, j, i, f_colour);
			mlx_put_pixel(cub->img->ceil, j, i, c_colour);
			j++;
		}
		i++;
	}
}

static void	init_images(t_cub *cub)
{
	mlx_texture_t	*temp;

	temp = mlx_load_png(cub->map->no);
	cub->img->no = mlx_texture_to_image(cub->mlx, temp);
	free(temp);
	temp = mlx_load_png(cub->map->so);
	cub->img->so = mlx_texture_to_image(cub->mlx, temp);
	free(temp);
	temp = mlx_load_png(cub->map->we);
	cub->img->we = mlx_texture_to_image(cub->mlx, temp);
	free(temp);
	temp = mlx_load_png(cub->map->ea);
	cub->img->ea = mlx_texture_to_image(cub->mlx, temp);
	free(temp);
	create_floor_ceil(cub);
	if (mlx_image_to_window(cub->mlx, cub->img->floor, 0, S_HEIGHT / 2) == -1)
		rerror("put_floor failed");
	if (mlx_image_to_window(cub->mlx, cub->img->ceil, 0, 0) == -1)
		rerror("put_ceil failed");
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
}

void	initialize(t_cub *cub)
{
	cub->img = ft_calloc(1, sizeof(t_img));
	init_images(cub);
}
