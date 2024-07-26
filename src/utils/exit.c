/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:15:48 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/26 16:51:39 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_data(t_data *data)
{
	printf("Freeing data 1\n");
	free(data->window);
	printf("2\n");
	free_map(&data->map);
	printf("3\n");
	ft_free_2d_arr((void **)data->texture);
	printf("4\n");
	// ft_free_2d_arr((void **)data->rgb);
	// printf("5\n");
	ft_free_2d_arr((void **)data->sprite_t);
	printf("6\n");
	free(data->z_buffer);
	printf("7\n");
	free(data->sprites);
	printf("8\n");
	// free(data);
	printf("9\n");
}

void	ft_exit(void)
{
	mlx_terminate(static_data()->window->mlx);
	free_data(static_data());
	exit(0);
}
