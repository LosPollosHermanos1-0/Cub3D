/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:02:24 by lzipp             #+#    #+#             */
/*   Updated: 2024/06/20 14:21:29 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

bool	ft_read_file(char **file, char ***map_ptr, char ***texture_ptr,
		int **rgb_ptr)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("Error: could not open file"), false);
	if (ft_get_textures_colors(fd, texture_ptr, rgb_ptr) == false)
		return (false);
	if (ft_get_map(fd, map_ptr) == false)
		return (false);
}

static bool	ft_get_textures_colors(int fd, char ***texture_ptr, int **rgb_ptr)
{
	char	*line;

	line =ft_get_next_line(fd);
	while (line)
	{
		if (ft_wrong_char_inside(&line) == true)
			return (free(line), perror("Error: invalid character in file"), false);
		line = ft_trim_in_place(line, " ");
		if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
			|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
			if (ft_get_texture(&line, texture_ptr) == false)
				return (false);
		else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
			if (ft_get_rgb_arr(&line, rgb_ptr) == false)
				return (false);
		else if (line[0] == '\n')
			;
		else
			return (free(line), perror("Error: invalid line"), false);
		free(line);
		line = ft_get_next_line(fd);
	}
	return (true);
}

int	main(void)
{
	char	**map;
	char	**textures;
	int		colors[2][3];

	char *filepath = "./test_files/test.cub";
	map = ft_calloc(1, sizeof(char *));
	textures = ft_calloc(5, sizeof(char *));
	
	if (ft_read_file(filepath, &map, &textures, &colors) == false)
		return (1);
	
	// do stuff with map, textures and colors
	return (0);
}
