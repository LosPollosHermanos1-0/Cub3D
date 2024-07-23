/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:03:40 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/23 22:03:48 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprites(t_data *data)
{
    data->sprites = malloc(sizeof(t_sprite_data) * data->opponent_count);
    if (data->sprites == NULL)
    {
        ft_putendl_fd("Error\nMalloc failed", 2);
        exit(EXIT_FAILURE);
    }
    ft_memset(data->sprites, 0, sizeof(t_sprite_data) * data->opponent_count);
    int x = 0;
    int y = 0;
    int sprite_count = 0;
    while (data->map->map[y])
    {
        x = 0;
        while (data->map->map[y][x] != END)
        {
            if (data->map->map[y][x] == OPPONENT)
            {
                data->sprites[sprite_count].pos = (t_vector_2d){y + 0.5, x + 0.5};
                data->sprites[sprite_count].dir = (t_vector_2d){1, 0};
                data->sprites[sprite_count].texture = 0;
                data->sprites[sprite_count].last_animation_change = 0;
                data->sprites[sprite_count].animation_speed = 0.2;
                data->sprites[sprite_count].move_speed = 0.02;
                sprite_count++;
            }
            x++;
        }
        y++;
    }
}
