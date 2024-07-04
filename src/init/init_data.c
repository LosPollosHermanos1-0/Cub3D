/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:36:32 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/04 13:07:41 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

static mlx_texture_t	**ft_load_texture(char ***textures);

t_data *init_data(char **filepath)
{
	t_data			*data;
	char			**textures;
	int				**rgb;
	e_map_elements	**map;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (printf("Error: Malloc failed\n"), NULL);
	data->player = NULL;
	data->texture = NULL;
	data->map = NULL;
	data->texture = NULL;
	if (data->map == NULL)
		return (free_data(data), NULL);
	if (ft_load_data(filepath, &textures, &rgb, &map) == false)
		return (free(data), NULL);
	data->window = init_window();
	data->map = init_map(&map);
	data->player = init_player(&map);
	data->texture = ft_load_texture(&textures);
	if (!data->window || !data->map || !data->player || !data->texture)
		return (free_data(data), NULL);
	return data;
}

static mlx_texture_t	**ft_load_texture(char ***textures)
{
	mlx_texture_t		**texture;

	texture = ft_calloc(7, sizeof(mlx_texture_t *));
	if ((*texture) == NULL)
		return (printf("Error: textures not allocated"), NULL);
	texture[NORTH] = mlx_load_png(texture[NORTH]);
	texture[SOUTH] = mlx_load_png(texture[SOUTH]);
	texture[WEST] = mlx_load_png(texture[WEST]);
	texture[EAST] = mlx_load_png(texture[EAST]);
	texture[FLOOR] = mlx_load_png(texture[FLOOR]);
	texture[CEILING] = mlx_load_png(texture[CEILING]);
	return (texture);
}

void	free_data(t_data **data)
{
	free_player((*data)->player);
	free_map((*data)->map);
	free(*data);
}
