/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:20:33 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/04 10:57:24 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

t_map *init_map(char **content)
{
	t_map *map = malloc(sizeof(t_map));
	if (map == NULL) {
		printf("Error: Malloc failed\n");
		exit(1);
	}
	map->map = NULL;
	if (ft_get_map(content, &(map->map)) == false)
		return (NULL);
	return map;
}
