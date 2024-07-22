/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:51:26 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/22 13:13:41 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	ft_floodfill(char ***map_ptr, int c, int r);
static bool	ft_copy_map(char ***map_ptr, char ***map_copy_ptr, int width,
				int height);
static bool	ft_only_valid_chars(char ***map_ptr);

/**
 * Validates the map.
 *
 * @param map Map to validate.
 * @return true if map is valid, false otherwise.
 */
bool	ft_validate_map(char ***map_ptr)
{
	int		*pos;
	char	**map_copy;
	char	**map_fill_copy;

	if (ft_only_valid_chars(map_ptr) == false)
		return (printf("Error: invalid characters in map\n"), false);
	pos = ft_get_player(map_ptr);
	if (!pos)
		return (free(pos), printf("Error: wrong number of players\n"), false);
	if (ft_copy_map(map_ptr, &map_fill_copy, ft_map_width(map_ptr),
			ft_map_height(map_ptr)) == false)
		return (free(pos), printf("Error: failed to copy map\n"), false);
	if (ft_floodfill(&map_fill_copy, pos[1], pos[0]) == false)
		return (free(pos), ft_free_2d_arr((void **)map_fill_copy),
			printf("Error: map is not valid\n"), false);
	ft_free_2d_arr((void **)map_fill_copy);
	if (ft_copy_map(map_ptr, &map_copy, ft_map_width(map_ptr),
			ft_map_height(map_ptr)) == false)
		return (free(pos), printf("Error: failed to copy map\n"), false);
	ft_free_2d_arr((void **)(*map_ptr));
	*map_ptr = map_copy;
	return (free(pos), true);
}

/**
 * Copies the map for floodfill.
 * @param map_ptr Map to copy.
 * @param map_copy_ptr Pointer to the copied map.
 * @param width Width of the map.
 * @param height Height of the map.
 * @return true if map was copied successfully, false otherwise.
 */
static bool	ft_copy_map(char ***map_ptr, char ***map_copy_ptr, int width,
		int height)
{
	int	i;
	int	j;
	int	row_len;

	(*map_copy_ptr) = ft_calloc(height + 1, sizeof(char *));
	if (!*map_copy_ptr)
		return (false);
	i = -1;
	while (++i < height)
	{
		(*map_copy_ptr)[i] = ft_calloc(width + 1, sizeof(char));
		if (!(*map_copy_ptr)[i])
			return (ft_free_2d_arr((void **)(*map_copy_ptr)), false);
		row_len = ft_strlen((*map_ptr)[i]);
		j = -1;
		while (++j < width && j < row_len)
			(*map_copy_ptr)[i][j] = (*map_ptr)[i][j];
		while (j < width)
			(*map_copy_ptr)[i][j++] = ' ';
	}
	return (true);
}

/**
 * Floodfill algorithm to validate the map.
 * @param map_ptr Map to validate.
 * @param c Column to start floodfill.
 * @param r Row to start floodfill.
 * @return true if map is valid, false otherwise.
 */
static bool	ft_floodfill(char ***map_ptr, int c, int r)
{
	(*map_ptr)[r][c] = '.';
	if (((r < 1 || (*map_ptr)[r - 1][c] == ' '
		|| (*map_ptr)[r - 1][c] == '\0'))
		|| ((!(*map_ptr)[r + 1] || (*map_ptr)[r + 1][c] == ' ' || (*map_ptr)[r
				+ 1][c] == '\0')) || ((c < 1 || (*map_ptr)[r][c - 1] == ' '
				|| (*map_ptr)[r][c - 1] == '\0')) || ((!(*map_ptr)[r][c + 1]
				|| (*map_ptr)[r][c + 1] == ' '
				|| (*map_ptr)[r][c + 1] == '\0')))
		return (false);
	if (r > 0 && ((*map_ptr)[r - 1][c] == '0' || (*map_ptr)[r - 1][c] == 'D'))
		if (ft_floodfill(map_ptr, c, r - 1) == false)
			return (false);
	if ((*map_ptr)[r + 1] && ((*map_ptr)[r + 1][c] == '0' || (*map_ptr)[r
			+ 1][c] == 'D'))
		if (ft_floodfill(map_ptr, c, r + 1) == false)
			return (false);
	if (c > 0 && ((*map_ptr)[r][c - 1] == '0' || (*map_ptr)[r][c - 1] == 'D'))
		if (ft_floodfill(map_ptr, c - 1, r) == false)
			return (false);
	if ((*map_ptr)[r][c + 1] && ((*map_ptr)[r][c + 1] == '0' || (*map_ptr)[r][c
			+ 1] == 'D'))
		if (ft_floodfill(map_ptr, c + 1, r) == false)
			return (false);
	return (true);
}

static bool	ft_only_valid_chars(char ***map_ptr)
{
	int	i;
	int	j;

	i = -1;
	while ((*map_ptr)[++i])
	{
		j = -1;
		while ((*map_ptr)[i][++j])
		{
			if ((*map_ptr)[i][j] != ' ' && (*map_ptr)[i][j] != '1'
				&& (*map_ptr)[i][j] != '0'
				&& (*map_ptr)[i][j] != 'N' && (*map_ptr)[i][j] != 'S'
				&& (*map_ptr)[i][j] != 'E' && (*map_ptr)[i][j] != 'W')
				// add all other chars here...
				return (false);
		}
	}
	return (true);
}
