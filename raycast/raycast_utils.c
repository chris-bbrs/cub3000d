/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 22:41:41 by cboubour          #+#    #+#             */
/*   Updated: 2023/01/13 15:35:08 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	dda(t_cub *cub)
{
	bool	hit;

	hit = false;
	while (hit == false)
	{
		if (cub->ray->side_dist_x < cub->ray->side_dist_y)
		{
			cub->ray->side_dist_x += cub->ray->delta_dist_x;
			cub->ray->pos_x += cub->ray->step_x;
			cub->ray->side = 0;
		}
		else
		{
			cub->ray->side_dist_y += cub->ray->delta_dist_y;
			cub->ray->pos_y += cub->ray->step_y;
			cub->ray->side = 1;
		}
		if (cub->map->tiles[cub->ray->pos_y][cub->ray->pos_x] == '1')
			hit = true;
	}
}

void	draw_bg(t_cub *cub, int raycount)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	f_colour;
	uint32_t	c_colour;
	static int	count = 0;

	count++;
	if (count == 1)
		return ;
	f_colour = (cub->map->f[0] << 24) | (cub->map->f[1] << 16);
	f_colour = f_colour | (cub->map->f[2] << 8) | 255;
	c_colour = (cub->map->c[0] << 24) | (cub->map->c[1] << 16);
	c_colour = c_colour | (cub->map->c[2] << 8) | 255;
	i = 0;
	while (i < S_HEIGHT)
	{
		if (i <= cub->draw_wall->draw_start)
			mlx_put_pixel(cub->img->b_img, raycount, i, c_colour);
		else if (i >= cub->draw_wall->draw_end)
			mlx_put_pixel(cub->img->b_img, raycount, i, f_colour);
		i++;
	}
}

static double	find_wall_x(t_cub *cub, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = cub->player->pos_y + (ray->wall_dist * ray->dir_y);
	else
	{
		wall_x = cub->player->pos_x + (ray->wall_dist * ray->dir_x);
	}
	wall_x -= floor(wall_x);
	return (wall_x);
}

static int	find_texture_x(t_cub *cub, mlx_texture_t *texture, t_ray *ray)
{
	int	tex_x;

	tex_x = (int)(find_wall_x(cub, ray) * (double)texture->width);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

void	draw_vertical_line(t_cub *cub, int raycount)
{
	int		i;
	int		sd;
	double	step;
	double	texture_pos;

	sd = cub->wall_direction;
	cub->tex->tex_x = find_texture_x(cub, cub->tex->tex[sd], cub->ray);
	step = ((double)cub->tex->tex[sd]->height) / cub->draw_wall->line_height;
	texture_pos = (cub->draw_wall->draw_start - (S_HEIGHT / 2)
			+ (cub->draw_wall->line_height / 2)) * step;
	i = cub->draw_wall->draw_start;
	while (i < cub->draw_wall->draw_end)
	{
		cub->tex->tex_y = (int)(texture_pos) & (cub->tex->tex[sd]->height - 1);
		texture_pos += step;
		ft_memcpy(&cub->img->b_img->pixels
		[(i * cub->img->b_img->width + raycount) * 4],
			&cub->tex->tex[sd]->pixels[(cub->tex->tex_y
				* cub->tex->tex[sd]->height + cub->tex->tex_x) * 4], 4);
		i++;
	}
}
