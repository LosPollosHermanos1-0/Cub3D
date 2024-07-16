/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:02:24 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/16 11:51:12 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_read_whole_file(char **content, int fd);
static int	ft_handle_after_map_start(int fd);
bool		ft_get_map_char(char **content, char ***map_ptr);
static void	ft_adjust_start(char **line, int i, int *start,
				bool *look_for_start);
static void	ft_join_helper(char **content, char **line_ptr, int *i);

/**
 * Loads textures, colors & maps from ther file.
 * @param filepath Path to the file.
 * @param texture_paths Array of texture paths.
 * @param f_and_c_color Array of floor and ceiling colors.
 * @param map_ptr Pointer to the map.
 */
bool	ft_load_data(char **filepath, char **texture_paths,
		t_rgb_color	**f_and_c_color, int ***map_ptr)
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
	if (ft_get_textures_rgb(&content, texture_paths, f_and_c_color) == false)
		return (free(content), false);
	if (ft_get_map(&content, map_ptr) == false)
		return (free(content), false);
	return (free(content), true);
}

/**
 * Reads in whole file content, returns line of map start.
 *
 * @param content File content.
 * @return The line at which the map was encountered or -1 if an error occured.
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
		ft_adjust_start(&line, i, &start, &look_for_start);
		if (ft_contains_only(line, " \n") == 0)
			ft_join_helper(content, &line, &i);
		else if (look_for_start == false && ft_contains_only(line, " \n") == 1
			&& ft_handle_after_map_start(fd) == -1)
			return (free(line), -1);
		free(line);
		if (*content == NULL)
			return (printf("Error: failed to append next line\n"), -1);
		line = get_next_line(fd);
	}
	return (free(line), start);
}

/**
 *
 * @param line_ptr pointer to the current line.
 * @param i current index.
 * @param start start of map.
 * @param look_for_start boolean to check if start is found.
 */
static void	ft_adjust_start(char **line_ptr, int i, int *start,
							bool *look_for_start)
{
	if ((*look_for_start) == true && ft_contains_only((*line_ptr), "1 \n") == 1
		&& ft_contains((*line_ptr), "1") == 1)
	{
		(*look_for_start) = false;
		(*start) = i;
	}
}

/**
 * Handles the content after the map.
 * @param fd File descriptor.
 */
static int	ft_handle_after_map_start(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (ft_contains(line, "\t\r\v") == 1)
			return (free(line), printf("Error: invalid character\n"), -1);
		if (ft_contains_only(line, " \n") == 1 && ft_contains(line, "\n") == 1)
			;
		else
			return (free(line),
				printf("Error: map should be last element!\n"), -1);
		free(line);
		line = get_next_line(fd);
	}
	return (free(line), 1);
}

static void	ft_join_helper(char **content, char **line_ptr, int *i)
{
	*content = ft_strjoin_in_place(*content, (*line_ptr));
	(*i)++;
}
