/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:36:32 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/27 17:39:09 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_texture_t	**init_sprite_helper(void);

bool	ft_set_data(char **filepath)
{
	t_data				*data;
	static char			*texture_paths[4];
	static t_rgb_color	*f_and_c_color[2];
	int					**map;

	data = static_data();
	if (ft_load_data(filepath, texture_paths, f_and_c_color, &map) == false)
		return (false);
	free(f_and_c_color[0]);
	free(f_and_c_color[1]);
	data->texture = init_texture(texture_paths);
	if (data->texture == NULL)
		return (false);
	data->window = init_window();
	if (data->window == NULL)
		return (false);
	data->map = init_map(&map);
	if (data->map == NULL)
		return (false);
	init_player(data);
	data->z_buffer = ft_calloc(data->window->width, sizeof(double));
	ft_memset(data->z_buffer, -1.0, sizeof(double) * data->window->width);
	data->sprite_t = init_sprite_helper();
	init_sprites(data);
	return (true);
}

static mlx_texture_t	**init_sprite_helper(void)
{
	mlx_texture_t	**sprite_t;

	sprite_t = malloc(sizeof(mlx_texture_t *) * 3);
	sprite_t[0] = mlx_load_png("textures/LostSoul.png");
	sprite_t[1] = mlx_load_png("textures/LostSoul2.png");
	sprite_t[2] = NULL;
	return (sprite_t);
}
