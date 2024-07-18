/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:44:05 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/18 16:40:27 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATIC_H
# define STATIC_H

# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05
# define WALL_DIST 0.1

typedef enum	e_map_elements t_map_elements;

typedef enum	e_textures {
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING
}				t_textures;

typedef struct	s_player {
	t_vector_2d pos;
	t_vector_2d dir;
	t_vector_2d plane;
	double move_speed;
	double rot_speed;
	double wall_dist;
}				t_player;

typedef struct	s_map {
	int	**map;
	int	width;
	int	height;
}				t_map;

typedef struct	s_minimap {
	int			**map;
	mlx_image_t	*minimap;
}				t_minimap;

typedef enum	e_data_flags
{
	FLAG_MOUSE_LOCKED = 1 << 0,
}				t_data_flags;

typedef struct	s_data  {
	t_window		*window;
	t_player		player;
	t_map			*map;
	t_minimap		*minimap;
	mlx_texture_t	**texture;
	int				**rgb;
	mlx_texture_t	**sprite_t;
	t_data_flags	flags;
	double*			z_buffer;
}				t_data;

void			free_data(t_data **data);
void			init_player(t_data *data);
void			free_player(t_player **player);
t_map			*init_map(int ***map_ptr);
void			free_map(t_map **map);
mlx_texture_t	**init_texture(char **texture_paths);
t_data			*static_data();

void		free_data(t_data **data);
bool		ft_set_data(char **filepath);

#endif
