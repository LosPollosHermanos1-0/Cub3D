/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:20:33 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/05 10:36:05 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

t_map *init_map(int ***map_ptr)
{
	t_map	*map;
	
	map = malloc(sizeof(t_map));
	if (map == NULL)
		return(printf("Error: map not allocated\n"), NULL);
	map->map = *map_ptr;
	return (map);
}

void	free_map(t_map **map)
{
	int	i;

	i = -1;
	while ((*map)->map[++i])
		free((*map)->map[i]);
	free((*map)->map);
	free(*map);
}
