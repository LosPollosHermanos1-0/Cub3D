/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 09:48:56 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/19 09:27:48 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct t_rgb_color
{
	int	r;
	int	g;
	int	b;
	int a;
}	t_rgb_color;

// enums
typedef enum	e_map_elements
{
	EMPTY,
	WALL,
	PLAYER_NO,
	PLAYER_SO,
	PLAYER_WE,
	PLAYER_EA,
	SPRITE,
	ITEM,
	DOOR,
	OUTSIDE,
	END
}				t_map_elements;

// structs
// typedef struct s_config
// {
// 	char			**textures;
// 	int				**rgb;
// }					t_config;

// typedef struct s_map
// {
// 	e_map_elements	**map;
// 	int				width;
// 	int				height;
// }					t_map;

// validate input
bool				ft_validate_input(int argc, char ***argv);

// load_data
bool				ft_load_data(char **filepath, char **texture_paths, t_rgb_color	**f_and_c_color,
						int ***map_ptr);
// map
bool				ft_get_map(char **content, int ***map_ptr);

// validate_map
bool				ft_validate_map(char ***map_ptr);

// map_utility
int					ft_map_width(char ***map_ptr);
int					ft_map_height(char ***map_ptr);
void				map_char_to_enum(int ***map_ptr, char **row_ptr, int i);
int					*ft_get_player(char ***map_ptr);

// rgb
bool				ft_get_rgb(char **line, t_rgb_color **f_and_c_color);

// textures
bool				ft_get_texture(char **line, char **texture_paths);
bool				ft_check_texture(char **texture);

// textures rgb
bool				ft_get_textures_rgb(char **content, char **texture_paths, t_rgb_color **f_and_c_color);

// helpers
bool				ft_wrong_char_inside(char **str);

// free
void				ft_free_texture_paths(char **texture_paths);

#endif
