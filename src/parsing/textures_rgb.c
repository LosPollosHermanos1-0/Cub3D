/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_rgb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:15:45 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/03 16:51:17 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	ft_validate_textures_rgb(char **texture_paths, int ***rgb_ptr);

bool	ft_get_textures_rgb(char **content, char **texture_paths, int ***rgb_ptr)
{
	int		i;
	char	**lines;

	lines = ft_split(*content, '\n');
	i = -1;
	while (++i < 6)
	{
		lines[i] = ft_strtrim_in_place(lines[i], " ");
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
			if (ft_get_rgb(&lines[i], rgb_ptr) == false)
				return (false);
		}
		else
			return (printf("Error: invalid line\n"), false);
	}
	return (ft_validate_textures_rgb(texture_paths, rgb_ptr));
}

static bool	ft_validate_textures_rgb(char **texture_paths, int ***rgb_ptr)
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
		if (!(*rgb_ptr)[i])
			return (printf("Error: missing color\n"), false);
	}
	return (true);
}
