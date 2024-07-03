/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:51:26 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/03 10:37:41 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

static bool	ft_flood_fill(char ***map_ptr, int x, int y);

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
	i = -1;
	while ((*map_ptr)[++i])
		printf("--||%s||--\n", (*map_ptr)[i]);
	return (true);
}

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
	int		i;

	pos = ft_get_player(map_ptr);
	if (!pos)
		return (printf("Error: player not found\n"), false);
	if (ft_copy_map(map_ptr, &map_copy, ft_map_width(map_ptr),
			ft_map_height(map_ptr)) == false)
		return (printf("Error: failed to copy map\n"), false);
	i = 0;
	while (map_copy[i])
		printf("||%s||\n", map_copy[i++]);
	printf("printed\n");
	if (!map_copy)
		return (printf("Error: failed to copy map\n"), false);
	printf("Map copied\n");
	if (ft_flood_fill(&map_copy, pos[0], pos[1]) == false)
	{
		ft_free_2d_arr((void **)map_copy);
		return (printf("Error: map is not valid\n"), false);
	}
	printf("Map is valid\n");
	return (ft_free_2d_arr((void **)map_copy), free(pos), true);
}

// static bool	ft_flood_fill(char ***map_ptr, int x, int y)
// {
// 	if (!(*map_ptr)[x] || !(*map_ptr)[x][y])
// 		return (true);
// 	if ((*map_ptr)[x][y] != '0' && (*map_ptr)[x][y] != 'N'
// 		&& (*map_ptr)[x][y] != 'S' && (*map_ptr)[x][y] != 'W'
// 		&& (*map_ptr)[x][y] != 'E' && (*map_ptr)[x][y] != 'D')
// 		return (false);
// 	(*map_ptr)[x][y] = '.';
// 	if (ft_flood_fill(map_ptr, x + 1, y) == false)
// 		return (false);
// 	if (ft_flood_fill(map_ptr, x - 1, y) == false)
// 		return (false);
// 	if (ft_flood_fill(map_ptr, x, y + 1) == false)
// 		return (false);
// 	if (ft_flood_fill(map_ptr, x, y - 1) == false)
// 		return (false);
// 	return (true);
// }

static bool	ft_flood_fill(char ***map_ptr, int c, int r)
{
	(*map_ptr)[r][c] = '.';
	if (((r <= 0 || (*map_ptr)[r - 1][c] == ' ' || (*map_ptr)[r
				- 1][c] == '\0')) || ((!(*map_ptr)[r + 1] || (*map_ptr)[r
				+ 1][c] == ' ' || (*map_ptr)[r + 1][c] == '\0')) || ((c <= 0
				|| (*map_ptr)[r][c - 1] == ' ' || (*map_ptr)[r][c - 1] == '\0'))
		|| ((!(*map_ptr)[r][c + 1] || (*map_ptr)[r][c + 1] == ' '
				|| (*map_ptr)[r][c + 1] == '\0')))
		return (false);
	if (r > 0 && ((*map_ptr)[r - 1][c] == '0' || (*map_ptr)[r - 1][c] == 'D'))
		if (!ft_flood_fill(map_ptr, c, r - 1))
			return (false);
	if ((*map_ptr)[r + 1] && ((*map_ptr)[r + 1][c] == '0' || (*map_ptr)[r
			+ 1][c] == 'D'))
		if (!ft_flood_fill(map_ptr, c, r + 1))
			return (false);
	if (c > 0 && ((*map_ptr)[r][c - 1] == '0' || (*map_ptr)[r][c - 1] == 'D'))
		if (!ft_flood_fill(map_ptr, c - 1, r))
			return (false);
	if ((*map_ptr)[r][c + 1] && ((*map_ptr)[r][c + 1] == '0' || (*map_ptr)[r][c
			+ 1] == 'D'))
		if (!ft_flood_fill(map_ptr, c + 1, r))
			return (false);
	return (true);
}
