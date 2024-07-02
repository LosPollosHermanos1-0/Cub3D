/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:51:26 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/02 12:19:07 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

/**
 * Validates the map.
 *
 * @param map Map to validate.
 * @return true if map is valid, false otherwise.
 */

bool	ft_validate_map(char ***map_ptr)
{
}

bool	ft_check_borders(char ***map_ptr)
{
	int	i;
	int	j;

	while ((*map_ptr)[0][i])
	{
		if ((*map_ptr)[0][i] != '1')
			return (printf("Error: map is not surrounded by walls\n"), false);
		i++;
	}
	{
		/* code */
	}
}

void	flood_fill_util(char ***map_ptr, int x, int y, char replacement)
{
	char	target;

	target = '0';
	if (!map_ptr[x][y] || (*map_ptr)[x][y] != target)
		return ;
	(*map_ptr)[x][y] = replacement;
	flood_fill_util(map_ptr, x + 1, y, replacement);
	flood_fill_util(map_ptr, x - 1, y, replacement);
	flood_fill_util(map_ptr, x, y + 1, replacement);
	flood_fill_util(map_ptr, x, y - 1, replacement);
}
