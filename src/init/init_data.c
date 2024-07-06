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

bool	ft_set_data(char **filepath)
{
	t_data *data;
	static char			*texture_paths[4];
	static t_rgb_color	*f_and_c_color[2];
	t_map_elements		**map;

	data = static_data();
	if (ft_load_data(filepath, texture_paths, f_and_c_color, &map) == false)
		return (false);
	// call only when bonus
	// when not bonus
	// data->rgb = rgb;
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
	return (true);
}

void	free_data(t_data **data)
{
	free_map(&((*data)->map));
	free(*data);
}
