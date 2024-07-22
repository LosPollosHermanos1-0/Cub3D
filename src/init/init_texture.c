/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:41:30 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/08 15:42:45 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_texture_t	**init_texture(char **texture_paths)
{
	mlx_texture_t		**texture;

	texture = ft_calloc(END + 1, sizeof(mlx_texture_t *));
	if (texture == NULL)
		return (printf("Error: texture not allocated"), NULL);
	texture[NORTH] = mlx_load_png(texture_paths[NORTH]);
	texture[SOUTH] = mlx_load_png(texture_paths[SOUTH]);
	texture[WEST] = mlx_load_png(texture_paths[WEST]);
	texture[EAST] = mlx_load_png(texture_paths[EAST]);
	texture[PILLAR] = mlx_load_png("textures/CEMENT6.png");
	texture[FLOOR] = mlx_load_png("textures/WOOD.png");
	texture[CEILING] = mlx_load_png("textures/ICKWALL2.png");
	texture[END] = NULL;

	ft_free_texture_paths(texture_paths);
	return (texture);
}
