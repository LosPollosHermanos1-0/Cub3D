/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_opponent2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:05:23 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/25 16:19:07 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MIN_DISTANCE 0.6
#define MIN_IDLE_TIME 1.0
#define MAX_IDLE_TIME 3.0
#define MAX_MOVE_TIME 2.0
#define CLOSE_DISTANCE_THRESHOLD 5.0

void	update_position(t_vector_2d move, t_sprite_data *opponent, t_data *data)
{
	t_movement_check	check;

	check = check_move_with_wall_dist(move, opponent->pos,
			data->player.wall_dist + 0.2);
	if (check.can_move_x && check.can_move_y && check.can_move_x_and_y)
		opponent->pos = ft_vector_add(opponent->pos, move);
	else if (check.can_move_x)
		opponent->pos.x += move.x;
	else if (check.can_move_y)
		opponent->pos.y += move.y;
}

void	move_opponent(t_data *data, t_sprite_data *opponent)
{
	t_vector_2d	move;
	double		move_length;

	move = ft_vector_sub(data->player.pos, opponent->pos);
	move_length = ft_vector_length(move);
	if (move_length > CLOSE_DISTANCE_THRESHOLD)
	{
		update_opponent_state(opponent);
		move = calculate_move(opponent, opponent->move_speed);
	}
	adjust_move_for_min_distance_between_opp(data, opponent, &move);
	move = normalize_and_scale_move(move, opponent->move_speed);
	update_position(move, opponent, data);
}

void	calculate_distance_to_player(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->opponent_count)
	{
		data->sprites[i].distance_to_player = calculate_distance(
				data->player.pos, data->sprites[i].pos);
	}
}

void	sort_sprites(t_data *data)
{
	int				i;
	int				j;
	t_sprite_data	temp;

	calculate_distance_to_player(data);
	i = -1;
	while (++i < data->opponent_count)
	{
		j = -1;
		while (++j < data->opponent_count - i - 1)
		{
			if (data->sprites[j].distance_to_player
				< data->sprites[j + 1].distance_to_player)
			{
				temp = data->sprites[j];
				data->sprites[j] = data->sprites[j + 1];
				data->sprites[j + 1] = temp;
			}
		}
	}
}
