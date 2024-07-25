/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_opponent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:40:16 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/25 15:47:46 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MIN_DISTANCE 0.6
#define MIN_IDLE_TIME 1.0
#define MAX_IDLE_TIME 3.0
#define MAX_MOVE_TIME 2.0
#define CLOSE_DISTANCE_THRESHOLD 5.0

double	random_double(double min, double max)
{
	return (min + (rand() / (RAND_MAX / (max - min))));
}

void	update_opponent_state(t_sprite_data *opponent)
{
	double	current_time;

	current_time = mlx_get_time();
	if (opponent->state == OPPONENT_IDLE)
	{
		if (current_time - opponent->last_idle > MAX_IDLE_TIME)
		{
			opponent->last_move = current_time;
			opponent->state = OPPONENT_WALKING;
			opponent->dir = ft_vector_normalize(
					(t_vector_2d){random_double(-1.0, 1.0),
					random_double(-1.0, 1.0)});
		}
	}
	else if (opponent->state == OPPONENT_WALKING)
	{
		if (current_time - opponent->last_move > MAX_MOVE_TIME)
		{
			opponent->last_idle = current_time;
			opponent->state = OPPONENT_IDLE;
		}
	}
}

t_vector_2d	calculate_move(t_sprite_data *opponent, double move_speed)
{
	if (opponent->state == OPPONENT_WALKING)
	{
		return (ft_vector_scale(opponent->dir, move_speed));
	}
	return ((t_vector_2d){0.0, 0.0});
}

void	adjust_move_for_min_distance_between_opp(t_data *data,
	t_sprite_data *opponent, t_vector_2d *move)
{
	int				i;
	t_sprite_data	*other_opponent;
	double			distance;
	t_vector_2d		direction_to_other;
	double			length_to_other;

	i = -1;
	while (++i < data->opponent_count)
	{
		other_opponent = &data->sprites[i];
		if (other_opponent == opponent)
			continue ;
		distance = calculate_distance(opponent->pos, other_opponent->pos);
		if (distance < MIN_DISTANCE)
		{
			direction_to_other = ft_vector_sub(opponent->pos,
					other_opponent->pos);
			length_to_other = ft_vector_length(direction_to_other);
			*move = ft_vector_add(*move, ft_vector_scale(direction_to_other,
						(MIN_DISTANCE - distance) / length_to_other));
		}
	}
}

t_vector_2d	normalize_and_scale_move(t_vector_2d move, double move_speed)
{
	double	move_length;

	move_length = ft_vector_length(move);
	if (move_length != 0)
	{
		move = ft_vector_scale(move, 1 / move_length);
		move = ft_vector_scale(move, move_speed);
	}
	return (move);
}
