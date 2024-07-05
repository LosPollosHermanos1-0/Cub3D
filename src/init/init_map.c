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

#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,3,2,1,4,2,0,0,0,0,4,0,2,0,1,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,4,0,0,0,1,0,0,0,0,3,0,0,0,2,0,0,0,1},
    {1,0,0,0,0,0,1,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,3,0,1,2,0,0,0,0,4,0,1,0,3,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,2,3,4,2,1,3,2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,3,0,2,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,5,0,4,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

t_map *init_map()
{
    t_map *map = malloc(sizeof(t_map));
    if (map == NULL) {
        printf("Error: Malloc failed\n");
        exit(1);
    }
    map->map = malloc(sizeof(int *) * 24);
    if (map->map == NULL) {
        printf("Error: Malloc failed\n");
        exit(1);
    }
    for (int i = 0; i < 24; ++i) {
        map->map[i] = malloc(sizeof(int) * 24);
        if (map->map[i] == NULL) {
            printf("Error: Malloc failed\n");
            exit(1);
        }
        for (int j = 0; j < 24; ++j) {
            map->map[i][j] = worldMap[i][j];
        }
    }
    return map;
}
