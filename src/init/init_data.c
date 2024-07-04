/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:36:32 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/04 11:02:39 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

t_data *init_data(char **filepath)
{
	t_data		*data;
	char		**rgb;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (printf("Error: Malloc failed\n"), NULL);
	if (ft_load_data(filepath, &(data->texture), &rgb, &(data->map->map)) == false)
		return (free(data), NULL);
	data->window = init_window();
	// data->map = init_map();
	data->player = init_player();
	// data->texture = malloc(sizeof(mlx_texture_t *) * 5);
	// data->texture[0] = mlx_load_png("textures/CEMENT1.png");
	// data->texture[1] = mlx_load_png("textures/CEMENT2.png");
	// data->texture[2] = mlx_load_png("textures/CEMENT3.png");
	// data->texture[3] = mlx_load_png("textures/CEMENT4.png");
	// data->texture[4] = mlx_load_png("textures/CEMENT5.png");
	return data;
}