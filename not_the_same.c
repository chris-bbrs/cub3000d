static double	find_wall_x(t_data *data, t_ray *ray)
{
	double	wall_x;

	if (ray->side <= 1)
		wall_x = data->player->pos.y + ray->wall_dist * ray->dir.y;
	else
		wall_x = data->player->pos.x + ray->wall_dist * ray->dir.x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

static int	find_texture_x(t_data *data, mlx_texture_t *texture, t_ray *ray)
{
	int	tex_x;

	tex_x = (int)(find_wall_x(data, ray) * (double) texture->width);
	if ((ray->side == 0 && ray->dir.x > 0)
		|| (ray->side == 1 && ray->dir.y < 0))
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

void	insert_textures(t_data *data, int x, int draw_start, int draw_end)
{
	mlx_texture_t	*texture;
	double			step;
	double			texture_pos;

	texture = data->png[data->ray.side];
	data->tex_x = find_texture_x(data, texture, &data->ray);
	step = (1.0 * texture->height) / (draw_end - draw_start);
	texture_pos = (draw_start - HEIGHT / 2 + (draw_end - draw_start)
			/ 2) * step;
	while (draw_start < draw_end)
	{
		data->tex_y = (int)(texture_pos) & (texture->height - 1);
		texture_pos += step;
		if (draw_start >= 0 && draw_start <= HEIGHT)
		{
			if (((draw_start * data->img->width + x) * 4)
				< (data->img->height * data->img->width * 4))
				ft_memcpy(&data->img->pixels[(draw_start * data->img->width + x)
					* 4], &texture->pixels[(data->tex_y
						* texture->height + data->tex_x) * 4], 4);
		}
		draw_start++;
	}
}