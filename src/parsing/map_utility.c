/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utility.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:52:41 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/23 16:35:57 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	ft_is_player(char c);

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

	i = 0;
	while ((*map_ptr)[i])
		i++;
	return (i);
}

/**
 * Maps a row of chars to their enum representations.
 * @param map_ptr Pointer to the map.
 * @param row_ptr Pointer to the row.
 * @param i Index of the row.
 */
void	map_char_to_enum(int ***map_ptr, char **row_ptr, int i)
{
	int		j;

	j = -1;
	while ((*row_ptr)[++j])
	{
		if ((*row_ptr)[j] == '0')
			(*map_ptr)[i][j] = EMPTY;
		else if ((*row_ptr)[j] == '1')
			(*map_ptr)[i][j] = WALL;
		else if ((*row_ptr)[j] == '2')
			(*map_ptr)[i][j] = PILLAR;
		else if ((*row_ptr)[j] == 'N')
			(*map_ptr)[i][j] = PLAYER_NO;
		else if ((*row_ptr)[j] == 'S')
			(*map_ptr)[i][j] = PLAYER_SO;
		else if ((*row_ptr)[j] == 'W')
			(*map_ptr)[i][j] = PLAYER_WE;
		else if ((*row_ptr)[j] == 'E')
			(*map_ptr)[i][j] = PLAYER_EA;
		else if ((*row_ptr)[j] == 'D')
			(*map_ptr)[i][j] = DOOR_CLOSED;
		else if ((*row_ptr)[j] == 'O') {
			static_data()->opponent_count++;
			(*map_ptr)[i][j] = OPPONENT;
		}
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
