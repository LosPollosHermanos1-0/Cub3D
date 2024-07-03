/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:07:59 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/03 15:51:20 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

static bool	ft_is_player(char c);
static bool	ft_get_map_char(char **content, char ***map_ptr);
static void	map_char_to_enum(e_map_elements ***map_ptr, char **row_ptr, int i);

/**
 * Gets the map from the content.
 * @param content Content to get map from.
 * @param map_ptr Pointer to the map.
 * @return true if map was successfully retrieved, false otherwise.
 */
bool	ft_get_map(char **content, e_map_elements ***map_ptr)
{
	int			i;
	int			width;
	char		**map_char;

	if (ft_get_map_char(content, &map_char) == false)
		return (false);
	(*map_ptr) = ft_calloc(ft_map_height(&map_char) + 1,
			sizeof(e_map_elements *));
	if (!(*map_ptr))
		return (false);
	i = -1;
	while (map_char[++i])
	{
		width = ft_strlen(map_char[i]);
		(*map_ptr)[i] = ft_calloc(width + 1, sizeof(e_map_elements));
		if (!(*map_ptr)[i])
			return (ft_free_2d_arr((void **)(*map_ptr)), false);
		printf("i succesful: %d\n", i);
		map_char_to_enum(map_ptr, &(map_char[i]), i);
		printf("i enum succesful: %d\n", i);
	}
	printf("map succesful\n");
	return (true);
}

/**
 * Gets the map from the content.
 *
 * @param content Content to get map from.
 * @param map_ptr Pointer to the map.
 * @return true if map was successfully retrieved, false otherwise.
 */
static bool	ft_get_map_char(char **content, char ***map_ptr)
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
	return (ft_validate_map(map_ptr));
}

/**
 * Maps a row of chars to their enum representations.
 * @param map_ptr Pointer to the map.
 * @param row_ptr Pointer to the row.
 * @param i Index of the row.
 */
static void	map_char_to_enum(e_map_elements ***map_ptr, char **row_ptr, int i)
{
	int		j;

	j = -1;
	while ((*row_ptr)[++j])
	{
		if ((*row_ptr)[j] == '0')
			(*map_ptr)[i][j] = EMPTY;
		else if ((*row_ptr)[j] == '1')
			(*map_ptr)[i][j] = WALL;
		else if ((*row_ptr)[j] == 'N')
			(*map_ptr)[i][j] = PLAYER_NO;
		else if ((*row_ptr)[j] == 'S')
			(*map_ptr)[i][j] = PLAYER_SO;
		else if ((*row_ptr)[j] == 'W')
			(*map_ptr)[i][j] = PLAYER_WE;
		else if ((*row_ptr)[j] == 'E')
			(*map_ptr)[i][j] = PLAYER_EA;
		else if ((*row_ptr)[j] == 'D')
			(*map_ptr)[i][j] = DOOR;
		else if ((*row_ptr)[j] == ' ')
			(*map_ptr)[i][j] = OUTSIDE;
	}
	(*map_ptr)[i][j] = END;
}

/**
 * Returns the players position.
 *
 * @param map_ptr Map to search player in.
 * @return row-col position if 1 player found, else NULL.
 */
int	*ft_get_player(char ***map_ptr)
{
	int		*pos;
	int		row;
	int		col;

	pos = NULL;
	row = -1;
	while ((*map_ptr)[++row])
	{
		col = -1;
		while ((*map_ptr)[row][++col])
		{
			if (ft_is_player((*map_ptr)[row][col]) && pos)
				return (free(pos), NULL);
			else if (ft_is_player((*map_ptr)[row][col]))
			{
				pos = malloc(2 * sizeof(int));
				if (!pos)
					return (NULL);
				pos[0] = row;
				pos[1] = col;
			}
		}
	}
	return (pos);
}

static bool	ft_is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

/**
 * Returns the width of the map.
 *
 * @param map Map to get width of.
 * @return Width of the map.
 */
int	ft_map_width(char ***map_ptr)
{
	int	i;
	int	j;
	int	width;

	i = -1;
	width = 0;
	while ((*map_ptr)[++i])
	{
		j = 0;
		while ((*map_ptr)[i][j])
			j++;
		if (j > width)
			width = j;
	}
	return (width);
}

/**
 * Returns the height of the map.
 *
 * @param map Map to get height of.
 * @return Height of the map.
 */
int	ft_map_height(char ***map_ptr)
{
	int	i;

	i = -1;
	while ((*map_ptr)[++i])
		;
	return (i);
}
