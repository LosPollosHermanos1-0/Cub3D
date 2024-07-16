/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_rgb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:15:45 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/16 13:22:27 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	ft_validate_textures_rgb(char **texture_paths,
				t_rgb_color **f_and_c_color);
static bool	ft_get_value(char **lines, char **texture_paths,
			t_rgb_color **f_and_c_color, int i);

bool	ft_get_textures_rgb(char **content, char **texture_paths,
			t_rgb_color **f_and_c_color)
{
	int		i;
	char	**lines;

	lines = ft_split(*content, '\n');
	if (lines == NULL)
		return (printf("Error: could not split content\n"), false);
	i = -1;
	while (++i < 6)
	{
		lines[i] = ft_strtrim_in_place(lines[i], " ");
		if (ft_get_value(lines, texture_paths, f_and_c_color, i) == false)
			return (ft_free_2d_arr((void **)lines), false);
	}
	return (ft_free_2d_arr((void **)lines),
		ft_validate_textures_rgb(texture_paths, f_and_c_color));
}

static bool	ft_get_value(char **lines, char **texture_paths,
			t_rgb_color **f_and_c_color, int i)
{
	if (ft_strncmp(lines[i], "NO ", 3) == 0 || ft_strncmp(lines[i], "SO ",
				3) == 0 || ft_strncmp(lines[i], "WE ", 3) == 0
			|| ft_strncmp(lines[i], "EA ", 3) == 0)
	{
		if (ft_get_texture(&lines[i], texture_paths) == false)
			return (false);
	}
	else if (ft_strncmp(lines[i], "F ", 2) == 0 || ft_strncmp(lines[i],
			"C ", 2) == 0)
	{
		if (ft_get_rgb(&lines[i], f_and_c_color) == false)
			return (false);
	}
	else
		return (printf("Error: invalid line\n"), false);
	return (true);
}


static bool	ft_validate_textures_rgb(char **texture_paths,
				t_rgb_color **f_and_c_color)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (texture_paths[i] == NULL)
			return (printf("Error: missing texture\n"), false);
	}
	i = -1;
	while (++i < 2)
	{
		if (f_and_c_color[i] == NULL)
			return (printf("Error: missing color\n"), false);
	}
	return (true);
}
