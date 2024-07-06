/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycast_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:44:47 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/03 02:44:51 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
inline t_vector_2d	calculate_delta_dist(t_vector_2d ray_dir)
{
    t_vector_2d	delta_dist;

    if (ray_dir.x != 0)
        delta_dist.x = fabs(1 / ray_dir.x);
    else
        delta_dist.x = INFINITY;
    if (ray_dir.y != 0)
        delta_dist.y = fabs(1 / ray_dir.y);
    else
        delta_dist.y = INFINITY;
    return (delta_dist);
}

t_raycast_data	init_raycast_data(const t_data *data, const int x)
{
    t_raycast_data	rd;
    
    rd.camera_x = 2 * x / (double)data->window->width - 1;
    rd.ray_dir = (t_vector_2d){data->player.dir.x + data->player.plane.x
        * rd.camera_x, data->player.dir.y + data->player.plane.y
        * rd.camera_x};
    rd.delta_dist = calculate_delta_dist(rd.ray_dir);
    rd.map = (t_coordinate){(int)data->player.pos.x,(int)data->player.pos.y};
    rd.side_dist = (t_vector_2d){0, 0};
    rd.perp_wall_dist = 0;
    rd.step = (t_coordinate){0,0};
    rd.hit = 0;
    rd.side = 0;
    rd.line_height = 0;
    return (rd);
}
