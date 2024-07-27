/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:36:32 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/27 17:28:46 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_set_data(char **filepath)
{
	t_data				*data;
	static char			*texture_paths[4];
	static t_rgb_color	*f_and_c_color[2];
	int					**map;

	data = static_data();
	if (ft_load_data(filepath, texture_paths, f_and_c_color, &map) == false)
		return (false);
	printf("1\n");
	free(f_and_c_color[0]);
	free(f_and_c_color[1]);
	printf("2\n");
	data->texture = init_texture(texture_paths);
	printf("3\n");
	if (data->texture == NULL)
		return (false);
	data->window = init_window();
	printf("4\n");
	if (data->window == NULL)
		return (false);
	data->map = init_map(&map);
	printf("5\n");
	if (data->map == NULL)
		return (false);
	init_player(data);
	printf("6\n");
	data->z_buffer = ft_calloc(data->window->width, sizeof(double));
	ft_memset(data->z_buffer, -1.0, sizeof(double) * data->window->width);
	data->sprite_t = malloc(sizeof(mlx_texture_t *) * 3);
	data->sprite_t[0] = mlx_load_png("textures/LostSoul.png");
	data->sprite_t[1] = mlx_load_png("textures/LostSoul2.png");
	data->sprite_t[2] = NULL;
	init_sprites(data);
	return (true);
}
