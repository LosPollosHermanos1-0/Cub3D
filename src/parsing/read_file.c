/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:02:24 by lzipp             #+#    #+#             */
/*   Updated: 2024/06/27 17:36:08 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

// static bool	ft_get_textures_colors(int fd, char ***texture_ptr, int **rgb_ptr);

// bool	ft_read_file(char **file, char ***map_ptr, char ***texture_ptr,
// 		int **rgb_ptr)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open(*file, O_RDONLY);
// 	if (fd == -1)
// 		return (close(fd), perror("Error: could not open file"), false);
// 	if (ft_get_textures_colors(fd, texture_ptr, rgb_ptr) == false)
// 		return (close(fd), false);
// 	if (ft_get_map(fd, map_ptr) == false)
// 		return (close(fd), false);
// 	close(fd);
// 	return (true);
// }

// static bool	ft_get_textures_colors(int fd, char ***texture_ptr, int **rgb_ptr)
// {
// 	char	*line;

// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		if (ft_wrong_char_inside(&line) == true)
// 			return (free(line), perror("Error: invalid character in file"),
// 				false);
// 		line = ft_strtrim_in_place(line, " ");
// 		if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
// 			|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ",
// 				3) == 0)
// 		{
// 			if (ft_get_texture(&line, texture_ptr) == false)
// 				return (false);
// 		}
// 		else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ",
// 				2) == 0)
// 		{
// 			if (ft_get_rgb_arr(&line, rgb_ptr) == false)
// 				return (false);
// 		}
// 		else if (line[0] == '\n')
// 			;
// 		else
// 			return (free(line), perror("Error: invalid line"), false);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	return (true);
// }


static bool	ft_get_textures_colors(char **content, char ***texture_ptr, int **rgb_ptr)
{
	int		i;
	char	**lines;

	lines = ft_split(*content, '\n');
	i = -1;
	while (++i < 6)
	{
		lines[i] = ft_strtrim_in_place(lines[i], " ");
		if (ft_strncmp(lines[i], "NO ", 3) == 0 || ft_strncmp(lines[i], "SO ", 3) == 0
			|| ft_strncmp(lines[i], "WE ", 3) == 0 || ft_strncmp(lines[i], "EA ",
				3) == 0)
		{
			if (ft_get_texture(&lines[i], texture_ptr) == false)
				return (false);
		}
		else if (ft_strncmp(lines[i], "F ", 2) == 0 || ft_strncmp(lines[i], "C ",
				2) == 0)
		{
			if (ft_get_rgb_arr(&lines[i], rgb_ptr) == false)
				return (false);
		}
		else
			return (perror("Error: invalid line"), false);
	}
	return (true);
}

static int	ft_load_config_from_file(char **filepath, e_map_elements ***map_ptr, char **texture_ptr, int **rgb_ptr)
{
	int		fd;
	int		start;
	char	*content;

	fd = open(*filepath, O_RDONLY);
	if (fd == -1)
		return (close(fd), perror("Error: could not open file"), -1);
	start = ft_read_whole_file(filepath, fd);
	if (start != 6)
		return (close(fd), perror("Error: config not formatted correctly"), false);
	if (ft_get_textures_colors(&content, texture_ptr, rgb_ptr) == false)
		return (close(fd), false);
	
}
{
	int		fd;
	int		start;

	fd = open(*filepath, O_RDONLY);
	if (fd == -1)
		return (close(fd), perror("Error: could not open file"), -1);
	start = ft_read_whole_file(filepath, fd);
	if (start != 6)
		return (close(fd), perror("Error: config not formatted correctly"), false);
	
}

/**
 * Reads in whole file content, returns line of map start.
 *
 * @param content File content.
 * @return The line at which the map was encountered OR -1 if an error occured.
 */
static int	ft_read_whole_file(char **content, int fd)
{
	char	*line;
	int		start;
	int		i;
	bool	look_for_start;

	start = -1;
	i = 0;
	look_for_start = true;
	line = get_next_line(fd);
	while (line)
	{
		if (ft_contains(line, "\t\r\v") == true)
			return (free(line), perror("Error: invalid character in file"), -1);
		if (look_for_start == true && ft_contains_only(line, "1 \n") == 1 && ft_contains(line, "1") == 1)
		{
			start = i;
			look_for_start = false;
		}
		if (!ft_contains_only(line, " \n"))
		{
			*content = ft_strjoin_in_place(*content, line);
			i++;
		}
		free(line);
		if (!(*content))
			return (perror("Error: failed to join content and next line"), -1);
		line = get_next_line(fd);
	}
	return (start);
}

#include <stdio.h>

int	main(void)
{
	char	*content = NULL;
	int		fd;
	int		start;

	fd = open("./test_files/test.cub", O_RDONLY);
	start = ft_read_whole_file(&content, fd);
	printf("start: %d\n", start);
	printf("content:\n%s\n", content);
	if (start == -1)
		return (1);
	return (0);
}
