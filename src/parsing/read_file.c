/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:02:24 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/01 15:22:06 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

static int	ft_read_whole_file(char **content, int fd);

/**
 * Loads the configuration from the file.
 *
 * @param filepath pointer to filepath.
 * @param texture_ptr Pointer to the texture array.
 * @param rgb_ptr Pointer to the rgb array.
 */
static bool	ft_load_config_from_file(char **filepath, char ***texture_ptr,
		int ***rgb_ptr)
{
	int		fd;
	int		start;
	char	*content;

	fd = open(*filepath, O_RDONLY);
	if (fd == -1)
		return (close(fd), printf("Error: could not open file\n"), -1);
	content = NULL;
	start = ft_read_whole_file(&content, fd);
	if (start != 6)
		return (close(fd), false);
	if (ft_get_textures_rgb(&content, texture_ptr, rgb_ptr) == false)
		return (close(fd), false);
	if (ft_validate_textures_rgb(texture_ptr, rgb_ptr) == false)
		return (close(fd), false);
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
		return (printf("Error: file is empty\n"), -1);
	while (line)
	{
		if (ft_contains(line, "\t\r\v") == true)
			return (free(line), printf("Error: invalid character in file\n"),
				-1);
		if (look_for_start == true && (bool)ft_contains_only(line,
				"1 \n") == true && (bool)ft_contains(line, "1") == true)
		{
			start = i;
			look_for_start = false;
		}
		else if (look_for_start == false && (bool)ft_contains_only(line,
				" \n") == true)
			return (printf("Error: map is invalid\n"), -1);
		if ((bool)ft_contains_only(line, " \n") == false)
		{
			*content = ft_strjoin_in_place(*content, line);
			i++;
		}
		free(line);
		if (!(*content))
		{
			return (printf("Error: failed to join content and next line\n"),
				-1);
		}
		line = get_next_line(fd);
	}
	return (start);
}

#include <stdio.h>

bool	test(char *filepath)
{
	char	**texture_ptr;
	int		**rgb_ptr;

	texture_ptr = ft_calloc(sizeof(char *), 5);
	rgb_ptr = ft_calloc(sizeof(int *), 3);
	if (!texture_ptr || !rgb_ptr)
		return (free(texture_ptr), free(rgb_ptr), 1);
	if (ft_load_config_from_file(&filepath, &texture_ptr, &rgb_ptr) == false)
		return (1);
	return (true);
}

int	main(void)
{
	printf("name: correct1: ");
	test("./test_files/correct1.cub");
	printf("-------------\n");
	printf("name: correct2: ");
	test("./test_files/correct2.cub");
	printf("-------------\n");
	printf("name: correct3: ");
	test("./test_files/correct3.cub");
	printf("-------------\n");
	printf("name: correct4: ");
	test("./test_files/correct4.cub");
	printf("-------------\n");
	printf("name: incorrect1: ");
	test("./test_files/incorrect1.cub");
	printf("-------------\n");
	printf("name: incorrect2: ");
	test("./test_files/incorrect2.cub");
	printf("-------------\n");
	printf("name: incorrect3: ");
	test("./test_files/incorrect3.cub");
	printf("-------------\n");
	printf("name: incorrect4: ");
	test("./test_files/incorrect4.cub");
	printf("-------------\n");
	printf("name: incorrect5: ");
	test("./test_files/incorrect5.cub");
	return (0);
}
