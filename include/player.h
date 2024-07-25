/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:16:41 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/25 16:50:08 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "cub3d.h"

typedef struct movement_check
{
	bool			can_move_x;
	bool			can_move_y;
	bool			can_move_x_and_y;
}					t_movement_check;

t_movement_check	check_move_with_wall_dist(const t_vector_2d move,
						const t_vector_2d player_pos, const double wall_dist);
void				move_player(t_data *d);
void				rotate_player(t_data *d, double angle);
void				rotate_player_mouse(double xpos, double ypos, void *param);

#endif // PLAYER_H
