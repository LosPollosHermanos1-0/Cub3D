/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:41:30 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/04 16:32:11 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_texture_t	**init_texture(char ***textures)
{
	mlx_texture_t		**texture;

	texture = ft_calloc(7, sizeof(mlx_texture_t *));
	if ((*texture) == NULL)
		return (printf("Error: texture not allocated"), NULL);
	texture[NORTH] = mlx_load_png((*textures)[NORTH]);
	texture[SOUTH] = mlx_load_png((*textures)[SOUTH]);
	texture[WEST] = mlx_load_png((*textures)[WEST]);
	texture[EAST] = mlx_load_png((*textures)[EAST]);
	// texture[FLOOR] = mlx_load_png("patgh/to/texture");
	// texture[CEILING] = mlx_load_png("patgh/to/texture");
	return (texture);
}
