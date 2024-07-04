/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:36:32 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/04 16:23:37 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

t_data	*init_data(void)
{
	t_data			*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (printf("Error: data not allocated\n"), NULL);
	data->player = NULL;
	data->texture = NULL;
	data->map = NULL;
	data->texture = NULL;
	data->rgb = NULL;
	return (data);
}

bool	ft_set_data(char **filepath, t_data **data_ptr)
{
	char			**textures;
	int				**rgb;
	e_map_elements	**map;

	if (ft_load_data(filepath, &textures, &rgb, &map) == false)
		return (false);
	// call only when bonus
	ft_free_rgb(&rgb);
	// when not bonus
	// (*data_ptr)->rgb = rgb;
	(*data_ptr)->texture = init_texture(&textures);
	ft_free_textures(&textures);
	if ((*data_ptr)->texture == NULL)
		return (false);
	(*data_ptr)->window = init_window();
	if ((*data_ptr)->window == NULL)
		return (false);
	(*data_ptr)->map = init_map(&map);
	if ((*data_ptr)->map == NULL)
		return (false);
	(*data_ptr)->player = init_player(&map);
	if ((*data_ptr)->player == NULL)
		return (false);
	return (true);
}

void	free_data(t_data **data)
{
	free_player(&((*data)->player));
	free_map(&((*data)->map));
	free(*data);
}
