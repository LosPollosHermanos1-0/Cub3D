/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:44:05 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/26 16:50:14 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATIC_H
# define STATIC_H

# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05
# define WALL_DIST 0.1
# define DOOR_INTERACTION_DIST 2.5

# include "cub3d.h"

typedef enum e_map_elements		t_map_elements;
typedef struct s_sprite_data	t_sprite_data;
typedef struct s_rgb_color		t_rgb_color;

typedef enum e_textures {
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING
}				t_textures;

typedef struct s_player {
	t_vector_2d		pos;
	t_vector_2d		dir;
	t_vector_2d		plane;
	double			move_speed;
	double			rot_speed;
	double			wall_dist;
}				t_player;

typedef struct s_map {
	int	**map;
	int	width;
	int	height;
}				t_map;

typedef enum e_data_flags
{
	FLAG_MOUSE_LOCKED = 1 << 0,
	FLAG_FACING_CLOSED_DOOR = 1 << 1,
	FLAG_FACING_OPEN_DOOR = 1 << 2,
}				t_data_flags;

typedef struct s_data {
	t_window		*window;
	t_player		player;
	t_map			*map;
	mlx_texture_t	**texture;
	mlx_texture_t	**sprite_t;
	t_data_flags	flags;
	double			*z_buffer;
	t_vector_2d		last_faced_open_door;
	t_vector_2d		last_faced_closed_door;
	int				opponent_count;
	t_sprite_data	*sprites;
	uint32_t		c_color;
	uint32_t		f_color;
}				t_data;

// void			free_data(t_data *data);
void			init_player(t_data *data);
void			free_player(t_player **player);
t_map			*init_map(int ***map_ptr);
void			free_map(t_map **map);
void			free_int_map(int **map);
mlx_texture_t	**init_texture(char **texture_paths);
t_data			*static_data(void);

bool			ft_set_data(char **filepath);
void			init_sprites(t_data *data);

#endif
