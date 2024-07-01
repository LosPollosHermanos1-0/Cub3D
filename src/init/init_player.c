/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:07:59 by jmoritz           #+#    #+#             */
/*   Updated: 2024/06/26 12:08:09 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player	*init_player()
{
    t_player	*player;

    player = malloc(sizeof(t_player));
    if (player == NULL) {
        printf("Error: Malloc failed\n");
        exit(1);
    }
    player->pos = ft_vector_init(22, 12);
    player->dir = ft_vector_init(-1, 0);
    player->plane = ft_vector_init(0, 0.66);
    player->move_speed = 0.1;
    player->wall_dist = 0.1;
    player->rot_speed = 0.05;
    return (player);
}