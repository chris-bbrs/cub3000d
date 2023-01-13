/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:02:50 by gjupy             #+#    #+#             */
/*   Updated: 2023/01/13 15:35:12 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	calc_ray(t_ray *ray, t_player *player, int raycount)
{
	ray->camera = 2 * raycount / (double) S_WIDTH - 1;
	ray->dir_x = player->dir_x + (player->plane_x
			* ray->camera);
	ray->dir_y = player->dir_y + (player->plane_y
			* ray->camera);
	ray->pos_x = (int) player->pos_x;
	ray->pos_y = (int) player->pos_y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = INFINITY;
	else
		ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = INFINITY;
	else
		ray->delta_dist_y = fabs(1.0 / ray->dir_y);
}

static void	calc_step_side_x(t_cub *cub)
{
	if (cub->ray->dir_x < 0)
	{
		cub->ray->step_x = -1;
		cub->ray->side_dist_x = (cub->player->pos_x - cub->ray->pos_x)
			* cub->ray->delta_dist_x;
		cub->potential_side_x = 2;
	}
	else
	{
		cub->ray->step_x = 1;
		cub->ray->side_dist_x = (cub->ray->pos_x + 1.0 - cub->player->pos_x)
			* cub->ray->delta_dist_x;
		cub->potential_side_x = 3;
	}
}

static void	calc_step_side_y(t_cub *cub)
{
	if (cub->ray->dir_y < 0)
	{
		cub->ray->step_y = -1;
		cub->ray->side_dist_y = (cub->player->pos_y - cub->ray->pos_y)
			* cub->ray->delta_dist_y;
		cub->potential_side_y = 0;
	}
	else
	{
		cub->ray->step_y = 1;
		cub->ray->side_dist_y = (cub->ray->pos_y + 1.0 - cub->player->pos_y)
			* cub->ray->delta_dist_y;
		cub->potential_side_y = 1;
	}
}

static void	calc_wall(t_cub *cub)
{
	if (cub->ray->side == 0)
	{
		cub->ray->wall_dist = (cub->ray->side_dist_x - cub->ray->delta_dist_x);
		cub->wall_direction = cub->potential_side_x;
	}
	else
	{
		cub->ray->wall_dist = (cub->ray->side_dist_y - cub->ray->delta_dist_y);
		cub->wall_direction = cub->potential_side_y;
	}
	cub->draw_wall->line_height = (int)(S_HEIGHT * 0.5) / cub->ray->wall_dist;
	cub->draw_wall->draw_start = (S_HEIGHT / 2)
		- (cub->draw_wall->line_height / 2);
	if (cub->draw_wall->draw_start < 0)
		cub->draw_wall->draw_start = 0;
	cub->draw_wall->draw_end = (S_HEIGHT / 2)
		+ (cub->draw_wall->line_height / 2);
	if (cub->draw_wall->draw_end >= S_HEIGHT)
		cub->draw_wall->draw_end = S_HEIGHT - 1;
}

void	raycast(t_cub *cub)
{
	int	raycount;

	raycount = 0;
	while (raycount < S_WIDTH)
	{
		calc_ray(cub->ray, cub->player, raycount);
		calc_step_side_x(cub);
		calc_step_side_y(cub);
		dda(cub);
		calc_wall(cub);
		draw_vertical_line(cub, raycount);
		draw_bg(cub, raycount);
		raycount++;
	}
}
