/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:15:48 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/27 17:33:22 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_data(t_data *data)
{
	free_map(&data->map);
	mlx_delete_texture(data->texture[NORTH]);
	mlx_delete_texture(data->texture[SOUTH]);
	mlx_delete_texture(data->texture[EAST]);
	mlx_delete_texture(data->texture[WEST]);
	mlx_delete_texture(data->texture[PILLAR]);
	mlx_delete_texture(data->texture[FLOOR]);
	mlx_delete_texture(data->texture[CEILING]);
	mlx_delete_texture(data->texture[DOOR_CLOSED]);
	free(data->texture);
	mlx_delete_texture(data->sprite_t[0]);
	mlx_delete_texture(data->sprite_t[1]);
	free(data->sprite_t);
	mlx_delete_texture(data->window->open_texture);
	mlx_delete_texture(data->window->close_texture);
	free(data->z_buffer);
	free(data->sprites);
}

void	ft_exit(void)
{
	free_data(static_data());
	mlx_terminate(static_data()->window->mlx);
	free(static_data()->window);
	exit(0);
}
