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

double	ft_vector_length(t_vector_2d vector)
{
    return (sqrt(vector.x * vector.x + vector.y * vector.y));
}

void	move_opponent(t_data *data, t_sprite_data *opponent)
{
    t_vector_2d move = ft_vector_sub(data->player.pos, opponent->pos);
    double move_length = ft_vector_length(move);
    const double MIN_DISTANCE = 0.6; // Minimum distance to maintain between opponents

    // Adjust movement to maintain minimum distance between opponents
    for (int i = 0; i < data->opponent_count; i++) {
        t_sprite_data *other_opponent = &data->sprites[i];
        if (other_opponent == opponent) continue; // Skip self

        double distance = calculate_distance(opponent->pos, other_opponent->pos);
        if (distance < MIN_DISTANCE) {
            t_vector_2d direction_to_other = ft_vector_sub(opponent->pos, other_opponent->pos);
            double length_to_other = ft_vector_length(direction_to_other);
            move = ft_vector_add(move, ft_vector_scale(direction_to_other, (MIN_DISTANCE - distance) / length_to_other));
        }
    }

    // Normalize and scale movement
    move_length = ft_vector_length(move);
    if (move_length != 0) {
        move = ft_vector_scale(move, 1 / move_length);
        move = ft_vector_scale(move, opponent->move_speed);
    }

    // Check movement with wall distance and update position
    t_movement_check check = check_move_with_wall_dist(move, opponent->pos, data->player.wall_dist + 0.2);
    if (check.can_move_x && check.can_move_y && check.can_move_x_and_y)
        opponent->pos = ft_vector_add(opponent->pos, move);
    else if (check.can_move_x)
        opponent->pos.x += move.x;
    else if (check.can_move_y)
        opponent->pos.y += move.y;
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
