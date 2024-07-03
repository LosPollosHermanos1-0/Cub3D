/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:44:05 by jmoritz           #+#    #+#             */
/*   Updated: 2024/06/26 12:19:16 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATIC_H
#define STATIC_H

typedef struct s_player {
    t_vector_2d pos;
    t_vector_2d dir;
    t_vector_2d plane;
    double move_speed;
    double rot_speed;
    double wall_dist;
} t_player;

typedef struct s_map {
    int **map;
} t_map;

typedef struct s_data  {
    t_window *window;
    t_player *player;
    t_map *map;
    mlx_texture_t **texture;
} t_data;

t_data      *init_data();
t_player	*init_player();
t_map       *init_map();
t_data      *static_data();

#endif
