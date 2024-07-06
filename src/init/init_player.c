/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:07:59 by jmoritz           #+#    #+#             */
/*   Updated: 2024/06/26 12:08:09 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	free_player(t_player **player)
{
	free(*player);
}

static t_vector_2d	ft_get_dir(t_map_elements player)
{
	if (player == PLAYER_EA)
		return (ft_vector_init(1, 0));
	if (player == PLAYER_NO)
		return (ft_vector_init(0, -1));
	if (player == PLAYER_SO)
		return (ft_vector_init(0, 1));
	if (player == PLAYER_WE)
		return (ft_vector_init(-1, 0));
	return (ft_vector_init(-1, -1));
}

static void	ft_get_pos_and_dir(t_data *data)
{
	int		row;
	int		col;

	row = -1;
	while (data->map->map[++row])
	{
		col = -1;
		while (data->map->map[row][++col])
		{
			if (data->map->map[row][col] == PLAYER_EA
				|| data->map->map[row][col] == PLAYER_NO
				|| data->map->map[row][col] == PLAYER_SO
				|| data->map->map[row][col] == PLAYER_WE)
			{
				data->player.pos = ft_vector_init(col, row);
				data->player.dir = ft_get_dir(data->map->map[row][col]);
			}
		}
	}
}

void	init_player(t_data *data)
{
	t_player	player;

	player = data->player;
	ft_get_pos_and_dir(data);
	player.plane = ft_vector_init(0, 0.66);
	player.move_speed = MOVE_SPEED;
	player.rot_speed = ROT_SPEED;
	player.wall_dist = WALL_DIST;
}
