/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:20:33 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/18 16:45:45 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

t_map *init_map(int ***map_ptr)
{
	t_map		*map;
	uint32_t	i;
	
	map = malloc(sizeof(t_map));
	if (map == NULL)
		return(printf("Error: map not allocated\n"), NULL);
	map->map = *map_ptr;
	i = 0;
	while (map->map[0][i] != END)
		i++;
	map->width = i + 1;
	i = 0;
	while (map->map[i])
		i++;
	map->height = i;
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
