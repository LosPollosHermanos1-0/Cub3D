/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_possible_move.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:16:16 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/25 17:06:17 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_possible_move(const t_vector_2d move)
{
	const t_map	*map = static_data()->map;

	return (map->map[(int)move.x][(int)move.y] < COLLIDABLE_START);
}

void	adjust_position(double move, double *new_pos, double wall_dist)
{
	if (move > 0)
		*new_pos += wall_dist;
	else
		*new_pos -= wall_dist;
}

t_movement_check	check_move_with_wall_dist(const t_vector_2d move,
	const t_vector_2d player_pos, const double wall_dist)
{
	t_vector_2d	adjusted_pos_x;
	t_vector_2d	adjusted_pos_y;
	t_vector_2d	adjusted_pos_xy;

	adjusted_pos_x = (t_vector_2d){player_pos.x + move.x, player_pos.y};
	adjusted_pos_y = (t_vector_2d){player_pos.x, player_pos.y + move.y};
	adjusted_pos_xy = (t_vector_2d){player_pos.x + move.x,
		player_pos.y + move.y};
	adjust_position(move.x, &adjusted_pos_x.x, wall_dist);
	adjust_position(move.y, &adjusted_pos_y.y, wall_dist);
	adjust_position(move.x, &adjusted_pos_xy.x, wall_dist);
	adjust_position(move.y, &adjusted_pos_xy.y, wall_dist);
	return ((t_movement_check){check_possible_move(adjusted_pos_x),
		check_possible_move(adjusted_pos_y),
		check_possible_move(adjusted_pos_xy)});
}
