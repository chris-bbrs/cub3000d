/* ************************************************************************** */
/*	                                                                          */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:16:27 by cboubour          #+#    #+#             */
/*   Updated: 2022/12/23 23:07:38 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_cub		*cub;

	if (argc == 2)
	{
		cub = (t_cub *)malloc(sizeof(t_cub));
		cub->map = initialize_map(argv[1]);
		cub->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3000d", true);
		if (!(cub->mlx))
			exit(EXIT_FAILURE);
		mlx_loop(cub->mlx);
		mlx_terminate(cub->mlx);
	}
	else
		printf("Error\nWrong number of arguments.\n");
	exit(EXIT_SUCCESS);
	return (0);
}
