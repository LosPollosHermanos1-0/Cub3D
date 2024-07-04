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
# define STATIC_H

typedef struct s_player
{
	t_vector_2d		pos;
	t_vector_2d		dir;
	t_vector_2d		plane;
	double			move_speed;
	double			rot_speed;
	double			wall_dist;
}				t_player;

typedef struct s_map
{
	int				**map;
}					t_map;

typedef enum e_data_flags
{
	FLAG_MOUSE_LOCKED = 1 << 0,
}					t_data_flags;

typedef struct s_data
{
	t_window		*window;
	t_player		*player;
	t_map			*map;
	mlx_texture_t	**texture;
	t_data_flags	flags;
	double*			z_buffer;
}					t_data;

t_data				*init_data(void);
t_player			*init_player(void);
t_map				*init_map(void);
t_data				*static_data(void);

#endif
