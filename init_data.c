/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:35:58 by gjupy             #+#    #+#             */
/*   Updated: 2023/01/04 16:53:35 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_structs(t_cub *cub)
{
	cub->player = malloc(sizeof(t_player));
	if (cub->player == NULL)
		exit(ENOMEM);
}

void	init_data(t_cub *cub)
{
	init_structs(cub);
	set_player(cub);
}