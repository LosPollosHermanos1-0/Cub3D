/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:36:32 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/05 10:34:30 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

t_data	*init_data(void)
{
	t_data			*data;

	data = static_data();
	return (data);
}

bool	ft_set_data(char **filepath, t_data **data_ptr)
{
	char			*texture_paths[4];
	int				**rgb;
	e_map_elements	**map;

	texture_paths[0] = NULL;
	texture_paths[1] = NULL;
	texture_paths[2] = NULL;
	texture_paths[3] = NULL;
	if (ft_load_data(filepath, texture_paths, &rgb, &map) == false)
		return (false);
	// call only when bonus
	ft_free_rgb(&rgb);
	// when not bonus
	// (*data_ptr)->rgb = rgb;
	(*data_ptr)->texture = init_texture(texture_paths);
	ft_free_texture_paths(texture_paths);
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
