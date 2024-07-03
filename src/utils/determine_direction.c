/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determine_direction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:43:36 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/03 02:44:04 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_direction	determine_direction(const t_vector_2d ray_dir, const int side)
{
    t_direction	direction;

    if (side == 0)
    {
        if (ray_dir.x < 0)
            direction = WEST;
        else
            direction = EAST;
    }
    else
    {
        if (ray_dir.y < 0)
            direction = NORTH;
        else
            direction = SOUTH;
    }
    return (direction);
}