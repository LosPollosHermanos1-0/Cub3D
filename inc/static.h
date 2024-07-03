/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:44:05 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/03 17:13:00 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATIC_H
#define STATIC_H

# include "parsing.h"

# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05
# define WALL_DIST 0.1

typedef struct	s_player {
	t_vector_2d pos;
	t_vector_2d dir;
	t_vector_2d plane;
	double move_speed;
	double rot_speed;
	double wall_dist;
}				t_player;

typedef struct	s_map {
	e_map_elements	**map;
}				t_map;

typedef struct	s_data  {
	t_window *window;
	t_player *player;
	t_map *map;
	mlx_texture_t **texture;
}				t_data;

t_data		*init_data();
t_player	*init_player();
t_map		*init_map();
t_data		*static_data();

#endif
