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

#include "./include/cub3d.h"

int	main(int argc, char *argv[])
{
	t_cub	cub;

	if (argc == 2)
	{
		cub.map = initialize_map(&cub, argv[1]);
		cub.mlx = mlx_init(S_WIDTH, S_HEIGHT, "cub3000d", true);
		if (!(cub.mlx))
			exit(ENOMEM);
		initialize(&cub);
		mlx_loop_hook(cub.mlx, &my_keyhook, &cub);
		mlx_loop(cub.mlx);
		exit_game_success(&cub);
	}
	else
		printf("Error\nWrong number of arguments.\n");
	exit(EXIT_SUCCESS);
}
