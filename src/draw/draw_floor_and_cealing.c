/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_and_cealing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 22:05:52 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/03 22:07:59 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



void draw_floor(t_data *data, int y) {
    const t_player *p = data->player;

    t_vector_2d left_boundry_ray = ft_vector_sub(p->dir, p->plane);
    t_vector_2d right_boundry_ray = ft_vector_add(p->dir, p->plane);

    int position_floor = y - data->window->height / 2;
    double row_distance_floor = (0.5 * data->window->height) / position_floor;
    t_vector_2d floor_step = ft_vector_div(ft_vector_scale(ft_vector_sub(right_boundry_ray, left_boundry_ray),  row_distance_floor) , (t_vector_2d){data->window->width, data->window->width});
    t_vector_2d floor = ft_vector_add(data->player->pos,ft_vector_scale(left_boundry_ray, row_distance_floor));

    for (int x = 0; x < data->window->width; ++x) {
        t_coordinate cell_floor = {(int)floor.x, (int)floor.y};
        t_coordinate texture_floor = {(int)(TEX_WIDTH * (floor.x - cell_floor.x)) & (TEX_WIDTH - 1), (int)(TEX_HEIGHT * (floor.y - cell_floor.y)) & (TEX_HEIGHT - 1)};
        floor = ft_vector_add(floor, floor_step);
        mlx_put_pixel(data->window->image, x, y, get_pixel(data->texture[2], texture_floor.x, texture_floor.y));
        mlx_put_pixel(data->window->image, x, data->window->height - y - 1 , get_pixel(data->texture[4], texture_floor.x, texture_floor.y));
    }
}
