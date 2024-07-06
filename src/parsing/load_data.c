/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:02:24 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/04 16:35:47 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_read_whole_file(char **content, int fd);
bool		ft_get_map_char(char **content, char ***map_ptr);

/**
 * Loads the configuration from the file.
 *
 * @param filepath pointer to filepath.
 * @param texture_paths Pointer to the texture array.
 * @param rgb_ptr Pointer to the rgb array.
 */
bool	ft_load_data(char **filepath, char **texture_paths, int ***rgb_ptr,
		e_map_elements ***map_ptr)
{
	int		fd;
	int		start;
	char	*content;

	fd = open(*filepath, O_RDONLY);
	if (fd == -1)
		return (close(fd), printf("Error: could not open file\n"), -1);
	content = ft_strdup("");
	start = ft_read_whole_file(&content, fd);
	if (start != 6)
	{
		if (start == -1)
			return (close(fd), free(content), false);
		else
			return (close(fd), free(content),
				printf("Error: config is not formatted correctly\n"), false);
	}
	close(fd);
	if (ft_get_textures_rgb(&content, texture_paths, rgb_ptr) == false)
		return (free(content), false);
	if (ft_get_map(&content, map_ptr) == false)
		return (free(content), false);
	int i = -1;
	int j;
	printf("\n");
	while ((*map_ptr)[++i])
	{
		j = -1;
		printf("{");
		while ((*map_ptr)[i][++j] != END)
			printf("%d,", (*map_ptr)[i][j]);
		printf("END},\n");
	}
	return (free(content), true);
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
		if (ft_contains(line, "\t\r\v") == 1)
			return (free(line), printf("Error: invalid character\n"), -1);
		if (look_for_start == true && ft_contains_only(line, "1 \n") == 1
			&& ft_contains(line, "1") == 1)
		{
			look_for_start = false;
			start = i;
		}
		if (ft_contains_only(line, " \n") == 0) //&& look_for_start == true)
		{
			*content = ft_strjoin_in_place(*content, line);
			i++;
		}
		else if (look_for_start == false && ft_contains_only(line, " \n") == 1)
			return (free(line), start);
		free(line);
		if (*content == NULL)
			return (printf("Error: failed to append next line\n"), -1);
		line = get_next_line(fd);
	}
	return (free(line), start);
}

