/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:07:59 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/03 15:59:31 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

static bool	ft_get_map_char(char **content, char ***map_ptr);

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
		map_char_to_enum(map_ptr, &(map_char[i]), i);
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
