/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determine_direction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:43:36 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/04 16:05:44 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_textures	determine_direction(const t_vector_2d ray_dir, const int side)
{
    t_textures	direction;

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
