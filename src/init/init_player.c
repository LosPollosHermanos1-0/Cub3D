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

// Rotate 90 degrees to the right and adjust to the desired magnitude
// Given the specific input vectors, this simplifies to swapping
// and negating with adjustment
t_vector_2d	get_perpendicular_vector(t_vector_2d dir)
{
	return (ft_vector_init(dir.y * 0.66, -dir.x * 0.66));
}

void	ft_set_dir_and_plane(int dir, t_data *data)
{
	if (dir == PLAYER_EA)
	{
		data->player.plane = ft_vector_init(0.66, 0);
		data->player.dir = ft_vector_init(0, 1);
	}
	else if (dir == PLAYER_NO)
	{
		data->player.plane = ft_vector_init(0, 0.66);
		data->player.dir = ft_vector_init(-1, 0);
	}
	else if (dir == PLAYER_WE)
	{
		data->player.plane = ft_vector_init(-0.66, 0);
		data->player.dir = ft_vector_init(0, -1);
	}
	else if (dir == PLAYER_SO) {
		data->player.plane = ft_vector_init(0, -0.66);
		data->player.dir = ft_vector_init(1, 0);
	}
}

static void	ft_get_pos_and_dir(t_data *data)
{
	int		row;
	int		col;

	row = -1;
	while (data->map->map[++row])
	{
		col = -1;
		while (data->map->map[row][++col] != END)
		{
			if (data->map->map[row][col] == PLAYER_EA
				|| data->map->map[row][col] == PLAYER_NO
				|| data->map->map[row][col] == PLAYER_SO
				|| data->map->map[row][col] == PLAYER_WE)
			{
				data->player.pos = ft_vector_init(row + 0.5, col +0.5);
				ft_set_dir_and_plane(data->map->map[row][col], data);
			}
		}
	}
}

void	init_player(t_data *data)
{
	ft_get_pos_and_dir(data);
	data->player.move_speed = MOVE_SPEED;
	data->player.rot_speed = ROT_SPEED;
	data->player.wall_dist = WALL_DIST;
}
