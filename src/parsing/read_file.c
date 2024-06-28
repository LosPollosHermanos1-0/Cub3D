/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:02:24 by lzipp             #+#    #+#             */
/*   Updated: 2024/06/28 14:42:00 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

// static bool	ft_get_textures_rgb(int fd, char ***texture_ptr, int **rgb_ptr);

// bool	ft_read_file(char **file, char ***map_ptr, char ***texture_ptr,
// 		int **rgb_ptr)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open(*file, O_RDONLY);
// 	if (fd == -1)
// 		return (close(fd), perror("Error: could not open file"), false);
// 	if (ft_get_textures_rgb(fd, texture_ptr, rgb_ptr) == false)
// 		return (close(fd), false);
// 	if (ft_get_map(fd, map_ptr) == false)
// 		return (close(fd), false);
// 	close(fd);
// 	return (true);
// }
static int	ft_read_whole_file(char **content, int fd);

static bool	ft_load_config_from_file(char **filepath, //e_map_elements ***map_ptr,
		char ***texture_ptr, int ***rgb_ptr)
{
	int		fd;
	int		start;
	char	*content;

	fd = open(*filepath, O_RDONLY);
	if (fd == -1)
		return (close(fd), perror("Error: could not open file"), -1);
	content = NULL;
	start = ft_read_whole_file(&content, fd);
	printf("after read_whole_file\n");
	if (start != 6)
		return (close(fd), perror("Error: config not formatted correctly"),
			false);
	if (ft_get_textures_rgb(&content, texture_ptr, rgb_ptr) == false)
		return (close(fd), false);
	printf("after get_textures_rgb\n");
	if (ft_validate_textures_rgb(texture_ptr, rgb_ptr) == false)
		return (close(fd), false);
	printf("after validate_textures_rgb\n");
	close(fd);
	return (true);
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
	if (!line)
		return (perror("Error: file is empty"), -1);
	while (line)
	{
		if (ft_contains(line, "\t\r\v") == true)
			return (free(line), perror("Error: invalid character in file"), -1);
		if (look_for_start == true && ft_contains_only(line, "1 \n") == 1
			&& ft_contains(line, "1") == 1)
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

// int	main(void)
// {
// 	char	*content;
// 	int		fd;
// 	int		start;

// 	content = NULL;
// 	fd = open("./test_files/test.cub", O_RDONLY);
// 	start = ft_read_whole_file(&content, fd);
// 	printf("start: %d\n", start);
// 	printf("content:\n%s\n", content);
// 	if (start == -1)
// 		return (1);
// 	return (0);
// }

int	main(void)
{
	char	*filepath;
	char	**texture_ptr;
	int		**rgb_ptr;

	filepath = "./test_files/test.cub";
	texture_ptr = ft_calloc(sizeof(char *), 5);
	rgb_ptr = ft_calloc(sizeof(int *), 3);
	if (!texture_ptr || !rgb_ptr)
		return (free(texture_ptr), free(rgb_ptr), 1);
	if (ft_load_config_from_file(&filepath, &texture_ptr, &rgb_ptr) == false)
		return (1);
	while(*texture_ptr)
	{
		printf("%s\n", *texture_ptr);
		texture_ptr++;
	}
	while (rgb_ptr)
	{
		printf("%d\n", **rgb_ptr);
		rgb_ptr++;
	}
	return (0);
}
