/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_opponents.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:54:12 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/28 12:55:33 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	ft_validate_opponents(char ***map_ptr)
{
	int		i;
	int		j;
	char	**map_fill_copy;

	i = -1;
	while ((*map_ptr)[++i])
	{
		j = -1;
		while ((*map_ptr)[i][++j])
		{
			if ((*map_ptr)[i][j] == 'O')
			{
				if (ft_copy_map(map_ptr, &map_fill_copy, ft_map_width(map_ptr),
						ft_map_height(map_ptr)) == false)
					return (printf("Error: failed to copy map\n"), false);
				if (ft_floodfill(&map_fill_copy, j, i) == false)
					return (ft_free_2d_arr((void **)map_fill_copy),
						printf("Error: map is not valid\n"), false);
				ft_free_2d_arr((void **)map_fill_copy);
			}
		}
	}
	return (true);
}
