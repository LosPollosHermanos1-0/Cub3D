/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:07:59 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/02 18:34:35 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

/**
 * Gets the map from the content.
 *
 * @param content Content to get map from.
 * @param map_ptr Pointer to the map.
 * @return true if map was successfully retrieved, false otherwise.
 */
bool	ft_get_map_char(char **content, char ***map_ptr)
{
	int		i;
	char	**rows;
	int		len;

	rows = ft_split(*content, '\n');
	if (!rows)
		return (printf("Error: failed to split map\n"), false);
	i = 5;
	len = 0;
	while (rows[++i])
		len++;
	(*map_ptr) = ft_calloc(len + 1, sizeof(char *));
	if (!(*map_ptr))
		return (ft_free_2d_arr((void **)rows), false);
	i = 5;
	len = 0;
	while (rows[++i])
	{
		(*map_ptr)[len] = ft_strdup(rows[i]);
		if (!((*map_ptr)[len]))
			return (ft_free_2d_arr((void **)rows), false);
		len++;
	}
	printf("\nmap:\n");
	while ((**map_ptr))
	{
		printf("%s\n", **map_ptr);
		(*map_ptr)++;
	}
	return (true);
}

/**
 * Returns the players position.
 *
 * @param map_ptr Map to search player in.
 * @return row-col position if found, else [-1, -1].
 */
// static int	*ft_get_player(char ***map_ptr)
// {
// 	int	row;
// 	int	col;

// 	row = -1;
// 	while ((*map_ptr)[++row])
// 	{
// 		col = -1;
// 		while ((*map_ptr)[row][++col])
// 		{
// 			if ((*map_ptr)[row][col] == 'N' || (*map_ptr)[row][col] == 'S'
// 				|| (*map_ptr)[row][col] == 'W' || (*map_ptr)[row][col] == 'E')
// 				return ((int[]){row, col});
// 		}
// 	}
// 	return (NULL);
// }

/**
 * Returns the width of the map.
 *
 * @param map Map to get width of.
 * @return Width of the map.
 */
// static int	ft_map_width(char ***map_ptr)
// {
// 	int	i;
// 	int	j;
// 	int	width;

// 	i = -1;
// 	width = 0;
// 	while ((*map_ptr)[++i])
// 	{
// 		j = -1;
// 		while ((*map_ptr)[i][++j])
// 			;
// 		if (j + 1 > width)
// 			width = j + 1;
// 	}
// 	return (width);
// }

/**
 * Returns the height of the map.
 *
 * @param map Map to get height of.
 * @return Height of the map.
 */
// static int	ft_map_height(char ***map_ptr)
// {
// 	int	i;

// 	i = -1;
// 	while ((*map_ptr)[++i])
// 		;
// 	return (i);
// }
