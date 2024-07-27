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
//	free(data->window);
	printf("2\n");
	free_map(&data->map);
	printf("3\n");
//	ft_free_2d_arr((void **)data->texture);
    mlx_delete_texture(data->texture[NORTH]);
    mlx_delete_texture(data->texture[SOUTH]);
    mlx_delete_texture(data->texture[EAST]);
    mlx_delete_texture(data->texture[WEST]);
    mlx_delete_texture(data->texture[PILLAR]);
    mlx_delete_texture(data->texture[FLOOR]);
    mlx_delete_texture(data->texture[CEILING]);
    mlx_delete_texture(data->texture[DOOR_CLOSED]);
    free(data->texture);
	printf("4\n");
	// ft_free_2d_arr((void **)data->rgb);
	// printf("5\n");
    mlx_delete_texture(data->sprite_t[0]);
    mlx_delete_texture(data->sprite_t[1]);
    free(data->sprite_t);

    mlx_delete_texture(data->window->open_texture);
    mlx_delete_texture(data->window->close_texture);

//    mlx_delete_texture(data->window->door_icon_close);
//    mlx_delete_texture(data->window->door_icon_open);
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
	free_data(static_data());
    mlx_terminate(static_data()->window->mlx);
    free(static_data()->window);
    exit(0);
}
