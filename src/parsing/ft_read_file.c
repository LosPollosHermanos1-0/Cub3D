/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 08:39:57 by vscode            #+#    #+#             */
/*   Updated: 2024/06/19 14:52:18 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

static void ft_read_textures_colors(int fd, char ***textures_ptr, int ***colors_ptr);

bool	ft_read_file(char *file_path, char ***textures_ptr,  int ***colors_ptr, char ***map_ptr)
{
	int			fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return(perror("Error: could not open file"), false);
	ft_read_textures_colors(fd, textures_ptr, colors_ptr);
	close(fd);
	return(ft_read_map(fd, map_ptr));
}

static void	ft_read_textures_colors(int fd, char ***textures_ptr, int ***colors_ptr)
{
	char	*line;

	line = ft_get_next_line(fd);
	while (line)
	{
		if (ft_includes_only(&line, "NOSWEAFC \t,1234567890") == false)
			return (free(line), perror("Error: invalid character in file"), false);
		line = ft_trim_in_place(line, " ");
		if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
			|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
			ft_get_texture(&line, textures_ptr);
		else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
			ft_get_rgb_arr(&line, colors_ptr);
		free(line);
		line = ft_get_next_line(fd);
	}
	return (true);
}

static bool	ft_includes_only(char **str, char ***valid)
{
	int		i;

	i = -1;
	while (*str[++i])
	{
		if (!ft_strchr(valid, *str))
			return (false);
		str++;
	}
	return (true);
}

static bool ft_get_texture(char **line, char ***textures_ptr)
{
	char	*texture;
	char	direction[3];
	int		fd;	

	ft_memmove(direction, *line, 2);
	direction[2] = NULL;
	texture = ft_strtrim(*line + 2, " ");
	if (ft_check_texture(&texture) == false)
		return (false);
}

static bool	ft_check_texture(char **texture)
{
	int	fd;

	if (ft_strrcmp(*texture, ".png", 4) != 0)
		return (perror("Error: texture must be of type .png"), false);
	fd = open(*texture, O_RDONLY);
	if (fd == -1)
		return (perror("Error: could not open texture"), false);
	close(fd);
	fd = open(*texture, O_DIRECTORY);
	if (fd != -1)
		return (perror("Error: texture must be a file"), false);
	return (close(fd), true);
}

static bool	ft_get_rgb_arr(char **line, int ***colors_ptr)
{
	char	*color;
	char	direction[3];
	char	**rgb_str;
	int		*rgb;

	ft_memmove(direction, *line, 1);
	direction[1] = NULL;
	color = ft_strtrim(*line + 1, " ");
	if (!color)
		return (perror("Error: could not get color"), false);
	rgb_str = ft_split(color, ',');
	free(color);
	if (!rgb_str)
		return (perror("Error: could not split color"), false);
	if (ft_null_terminated_arr_len(rgb_str) != 3)
		return (perror("Error: color must be a single path"), false);
	rgb = (int *)malloc(sizeof(int) * 3);
	if (!rgb)
		return (perror("Error: could not allocate memory for color"), false);
	rgb[0] = ft_atoi(rgb_str[0]);
	rgb[1] = ft_atoi(rgb_str[1]);
	rgb[2] = ft_atoi(rgb_str[2]);
	ft_null_terminated_arr_free(rgb_str);
	return (ft_null_terminated_arr_add(colors_ptr, rgb));
}