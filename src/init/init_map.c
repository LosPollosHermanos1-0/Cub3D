/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:20:33 by jmoritz           #+#    #+#             */
/*   Updated: 2024/06/26 12:20:37 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

t_map *init_map()
{
    t_map *map = malloc(sizeof(t_map));
    if (map == NULL) {
        printf("Error: Malloc failed\n");
        exit(1);
    }
    map->player_x = WINDOW_W / 2;
    map->player_y = WINDOW_H / 2;
    return map;
}