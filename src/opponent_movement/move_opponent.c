/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_opponent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:40:16 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/23 22:40:19 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

# define MIN_DISTANCE 0.6
# define MIN_IDLE_TIME 1.0
# define MAX_IDLE_TIME 3.0
# define MAX_MOVE_TIME 2.0
# define CLOSE_DISTANCE_THRESHOLD 5.0



double random_double(double min, double max) {
    return min + (rand() / (RAND_MAX / (max - min)));
}

void	update_opponent_state(t_sprite_data *opponent) {
    double current_time = mlx_get_time();
    if (opponent->state == OPPONENT_IDLE) {
        if (current_time - opponent->last_idle > MAX_IDLE_TIME) {
            opponent->last_move = current_time;
            opponent->state = OPPONENT_WALKING;
            opponent->dir = ft_vector_normalize((t_vector_2d){random_double(-1.0, 1.0), random_double(-1.0, 1.0)});
        }
    } else if (opponent->state == OPPONENT_WALKING) {
        if (current_time - opponent->last_move > MAX_MOVE_TIME) {
            opponent->last_idle = current_time;
            opponent->state = OPPONENT_IDLE;
        }
    }
}

t_vector_2d	calculate_move(t_sprite_data *opponent, double move_speed) {
    if (opponent->state == OPPONENT_WALKING) {
        return ft_vector_scale(opponent->dir, move_speed);
    }
    return (t_vector_2d){0.0, 0.0};
}

void	adjust_move_for_min_distance_between_opp(t_data *data, t_sprite_data *opponent, t_vector_2d *move) {
    for (int i = 0; i < data->opponent_count; i++) {
        t_sprite_data *other_opponent = &data->sprites[i];
        if (other_opponent == opponent) continue;

        double distance = calculate_distance(opponent->pos, other_opponent->pos);
        if (distance < MIN_DISTANCE) {
            t_vector_2d direction_to_other = ft_vector_sub(opponent->pos, other_opponent->pos);
            double length_to_other = ft_vector_length(direction_to_other);
            *move = ft_vector_add(*move, ft_vector_scale(direction_to_other, (MIN_DISTANCE - distance) / length_to_other));
        }
    }
}

t_vector_2d	normalize_and_scale_move(t_vector_2d move, double move_speed) {
    double move_length = ft_vector_length(move);
    if (move_length != 0) {
        move = ft_vector_scale(move, 1 / move_length);
        move = ft_vector_scale(move, move_speed);
    }
    return move;
}

void	update_position(t_vector_2d move, t_sprite_data *opponent, t_data *data) {
    t_movement_check check = check_move_with_wall_dist(move, opponent->pos, data->player.wall_dist + 0.2);
    if (check.can_move_x && check.can_move_y && check.can_move_x_and_y)
        opponent->pos = ft_vector_add(opponent->pos, move);
    else if (check.can_move_x)
        opponent->pos.x += move.x;
    else if (check.can_move_y)
        opponent->pos.y += move.y;
}

void	move_opponent(t_data *data, t_sprite_data *opponent) {
    t_vector_2d move = ft_vector_sub(data->player.pos, opponent->pos);
    double move_length = ft_vector_length(move);

    if (move_length > CLOSE_DISTANCE_THRESHOLD) {
        update_opponent_state(opponent);
        move = calculate_move(opponent, opponent->move_speed);
    }

    adjust_move_for_min_distance_between_opp(data, opponent, &move);
    move = normalize_and_scale_move(move, opponent->move_speed);
    update_position(move, opponent, data);
}

void calculate_distance_to_player(t_data *data)
{
    for (int i = 0; i < data->opponent_count; i++)
    {
        data->sprites[i].distance_to_player = calculate_distance(data->player.pos, data->sprites[i].pos);
    }
}


void sort_sprites(t_data *data)
{
    calculate_distance_to_player(data);
    for (int i = 0; i < data->opponent_count; i++)
    {
        for (int j = 0; j < data->opponent_count - i - 1; j++)
        {
            if (data->sprites[j].distance_to_player < data->sprites[j + 1].distance_to_player)
            {
                t_sprite_data temp = data->sprites[j];
                data->sprites[j] = data->sprites[j + 1];
                data->sprites[j + 1] = temp;
            }
        }
    }
}
