/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:02:50 by gjupy             #+#    #+#             */
/*   Updated: 2023/01/09 15:32:28 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda(t_cub *cub)
{
	bool	hit;

	hit = false;
	while (hit == false)
	{
		// jump to next map square, either in x-direction, or in y-direction
		if (cub->ray->sideDist_x < cub->ray->sideDist_y)
		{
			cub->ray->sideDist_x += cub->ray->deltaDist_x;
			cub->ray->pos_x += cub->ray->step_x;
			cub->ray->side = 0;
			if (cub->ray->dir_x > 0)
				cub->ray->side = 1;
		}
		else
		{
			cub->ray->sideDist_y += cub->ray->deltaDist_y;
			cub->ray->pos_y += cub->ray->step_y;
			cub->ray->side = 2;
			if (cub->ray->dir_y > 0)
				cub->ray->side = 3; // we never get into this one
		}
		// Check if ray has hit a wall
		if (cub->map->tiles[cub->ray->pos_y][cub->ray->pos_x] == '1')
			hit = true;
	}
}

static double	find_wall_x(t_cub *cub, t_ray *ray)
{
	double	wall_x;

	if (ray->side <= 1)
		wall_x = cub->player->pos_y + ray->wallDist * ray->dir_y;
	else
		wall_x = cub->player->pos_x + ray->wallDist * ray->dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

static int	find_texture_x(t_cub *cub, mlx_texture_t *texture, t_ray *ray)
{
	int	tex_x;

	tex_x = (int)(find_wall_x(cub, ray) * (double) texture->width);
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

	sd = cub->ray->side;
	cub->tex->tex_x = find_texture_x(cub, cub->tex->tex[sd], cub->ray);
	step = (1.0 * cub->tex->tex[sd]->height) / (cub->draw_wall->drawEnd - cub->draw_wall->drawStart);
	texture_pos = (cub->draw_wall->drawStart - S_HEIGHT / 2 + (cub->draw_wall->drawEnd - cub->draw_wall->drawStart)
			/ 2) * step;
	i = cub->draw_wall->drawStart;
	while (i <= cub->draw_wall->drawEnd)
	{
		cub->tex->tex_y = (int)(texture_pos) & (cub->tex->tex[sd]->height - 1);
		texture_pos += step;
		if (cub->draw_wall->drawStart >= 0 && cub->draw_wall->drawStart <= S_HEIGHT)
		{
			ft_memcpy(&cub->img->b_img->pixels[(i * cub->img->b_img->width + raycount) * 4],
			&cub->tex->tex[sd]->pixels[(cub->tex->tex_y
							* cub->tex->tex[sd]->height + cub->tex->tex_x) * 4], 4);
		}
		i++;
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
	c_colour = c_colour | (cub->map->c[2]  << 8) | 255;
	i = 0;
	while (i < S_HEIGHT)
	{
		if (i < cub->draw_wall->drawStart)
			mlx_put_pixel(cub->img->b_img, raycount, i, c_colour);
		else if (i > cub->draw_wall->drawEnd)
			mlx_put_pixel(cub->img->b_img, raycount, i, f_colour);
		i++;
	}
}

static void	reset_ray(t_ray *ray)
{
	ray->camera = 0;
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->pos_x = 0;
	ray->pos_y = 0;
	ray->sideDist_x = 0;
	ray->sideDist_y = 0;
	ray->deltaDist_x = 0;
	ray->deltaDist_y = 0;
	ray->side = 0;
	ray->wallDist = 0;
}

void	raycast(t_cub *cub)
{
	int	raycount;

	raycount = 0;
	while (raycount < S_WIDTH)
	{
		// reset_ray(cub->ray);
		// calculate ray position and direction
		cub->ray->camera = (2 * raycount) / (float) S_WIDTH - 1;
		cub->ray->dir_x = cub->player->dir_x + cub->player->plane_x
		* cub->ray->camera;
		cub->ray->dir_y = cub->player->dir_y + cub->player->plane_y
		* cub->ray->camera;
		// length of ray from one x or y-side to next x or y-side
		// deltaDist: length of ray from current position to next x or y-side
		// if (cub->ray->dir_x == 0)
		// 	cub->ray->deltaDist_x = INFINITY;
		// else
		// 	cub->ray->deltaDist_x = fabs(1.0 / cub->ray->dir_x);
		// if (cub->ray->dir_y == 0)
		// 	cub->ray->deltaDist_y = INFINITY;
		// else
		// 	cub->ray->deltaDist_y = fabs(1.0 / cub->ray->dir_y);
		cub->ray->deltaDist_x = fabs(1.0 / cub->ray->dir_x);
		cub->ray->deltaDist_y = fabs(1.0 / cub->ray->dir_y);
		// which box of the map we're in
		cub->ray->pos_x = (int) cub->player->pos_x;
		cub->ray->pos_y = (int) cub->player->pos_y;
		// step: what direction to step in x or y-direction (either +1 or -1)
		//calculate step and initial sideDist
		if (cub->ray->dir_x < 0)
		{
			cub->ray->step_x = -1;
			cub->ray->sideDist_x = (cub->player->pos_x - cub->ray->pos_x) * cub->ray->deltaDist_x;
		}
		else
		{
			cub->ray->step_x = 1;
			cub->ray->sideDist_x = (cub->ray->pos_x + 1.0 - cub->player->pos_x) * cub->ray->deltaDist_x;
		}
		if (cub->ray->dir_y < 0)
		{
			cub->ray->step_y = -1;
			cub->ray->sideDist_y = (cub->player->pos_y - cub->ray->pos_y) * cub->ray->deltaDist_y;
		}
		else
		{
			cub->ray->step_y = 1;
			cub->ray->sideDist_y = (cub->ray->pos_y + 1.0 - cub->player->pos_y) * cub->ray->deltaDist_y;
		}
		// cub->ray->pos_x = (int) cub->player->pos_x;
		// cub->ray->pos_y = (int) cub->player->pos_y;
		dda(cub);
		//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if (cub->ray->side <= 1)
			cub->ray->wallDist = (cub->ray->sideDist_x - cub->ray->deltaDist_x);
		else
			cub->ray->wallDist = (cub->ray->sideDist_y - cub->ray->deltaDist_y);
		//Calculate height of line to draw on screen
		cub->draw_wall->lineHeight = (int)(S_HEIGHT * 0.5 / cub->ray->wallDist);
		//calculate lowest and highest pixel to fill in current stripe
		cub->draw_wall->drawStart = -cub->draw_wall->lineHeight / 2 + S_HEIGHT / 2;
			if(cub->draw_wall->drawStart < 0)
				cub->draw_wall->drawStart = 0;
		cub->draw_wall->drawEnd = cub->draw_wall->lineHeight / 2 + S_HEIGHT / 2;
			if (cub->draw_wall->drawEnd >= S_HEIGHT)
				cub->draw_wall->drawEnd = S_HEIGHT - 1;
		draw_vertical_line(cub, raycount);
		draw_bg(cub, raycount);
		raycount++;
	}
}