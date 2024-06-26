/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:02:24 by lzipp             #+#    #+#             */
/*   Updated: 2024/06/26 14:21:11 by lzipp            ###   ########.fr       */
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
	i = -1;
	look_for_start = true;
	line = get_next_line(fd);
	while (line)
	{
		i++;
		if (ft_contains(line, "\t\r\v") == true)
			return (free(line), perror("Error: invalid character in file"), -1);
        printf("contains only: %d\n", ft_contains_only(line, "1 \n"));
        printf("contains: %d\n", ft_contains(line, "1"));
		if (look_for_start == true && ft_contains_only(line, "1 \n") == 1 && ft_contains(line, "1") == 1)
		{
			printf("triggered\n");
            start = i;
			look_for_start = false;
		}
		*content = ft_strjoin_in_place(*content, line);
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
    int     start;

    fd = open("./test_files/test.cub", O_RDONLY);
    start = ft_read_whole_file(&content, fd);
    printf("start: %d\n", start);
    printf("content:\n%s\n", content);
    if (start == -1)
        return (1);
    return (0);
}
