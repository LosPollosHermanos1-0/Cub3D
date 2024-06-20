/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 09:48:56 by lzipp             #+#    #+#             */
/*   Updated: 2024/06/20 14:23:09 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>

# include "../libft/libft.h"

// read_file
bool	ft_read_file(char **file, char ***map_ptr, char ***texture_ptr,
		int **rgb_ptr);
bool	ft_get_textures_colors(int fd, char ***texture_ptr, int **rgb_ptr);

// map
bool	ft_create_map(int fd, char*** map);

// rgb
bool	ft_get_rgb_arr(char **line, int ***colors_ptr);

// textures
bool	ft_get_texture(char **line, char ***textures_ptr);
bool	ft_check_texture(char **texture);

// helpers
bool	ft_wrong_char_inside(char **str);

// free
void	free_textures(char ***textures);
void	free_map(char ***map);

#endif
