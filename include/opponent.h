/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opponent.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:20:09 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/25 16:15:18 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPPONENT_H
# define OPPONENT_H

# include "cub3d.h"

typedef enum e_opponent_state
{
	OPPONENT_IDLE,
	OPPONENT_WALKING,
	OPPONENT_ATTACKING,
	OPPONENT_DEAD
}				t_opponent_state;

void		update_opponent_state(t_sprite_data *opponent);
t_vector_2d	calculate_move(t_sprite_data *opponent, double move_speed);
t_vector_2d	normalize_and_scale_move(t_vector_2d move, double move_speed);
void		adjust_move_for_min_distance_between_opp(t_data *data,
				t_sprite_data *opponent, t_vector_2d *move);

#endif //OPPONENT_H
