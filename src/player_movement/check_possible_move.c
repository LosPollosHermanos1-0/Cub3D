/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_possible_move.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:16:16 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/02 10:16:22 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_possible_move(const t_vector_2d move)
{
	const t_map	*map = static_data()->map;

	return (map->map[(int)move.x][(int)move.y] == 0);
}

void	adjust_position(double *move, double wall_dist)
{
	if (move > 0)
		*move += wall_dist;
	else
		*move -= wall_dist;
}

t_movement_check	*check_move_with_wall_dist(const t_vector_2d movement)
{
	const t_player *player = static_data()->player;

	t_vector_2d adjusted_pos_x = {movement.x, player->pos.y};
	t_vector_2d adjusted_pos_y = {player->pos.x, movement.y};
	t_vector_2d adjusted_pos_xy = {movement.x, movement.y};

	adjust_position(&adjusted_pos_x.x, player->wall_dist);
	adjust_position(&adjusted_pos_y.y, player->wall_dist);
	adjust_position(&adjusted_pos_xy.x, player->wall_dist);
	adjust_position(&adjusted_pos_xy.y, player->wall_dist);

	return (&(t_movement_check){check_possible_move(adjusted_pos_x),
		check_possible_move(adjusted_pos_y),
		check_possible_move(adjusted_pos_xy)});
}