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

inline void draw_floor_and_ceiling(t_data *data, int y) {
    const t_player *p = data->player;
    double half_height = data->window->height / 2.0;
    double position = y - half_height;
    double row_distance = half_height / position;

    t_vector_2d ray_dir_left = ft_vector_sub(p->dir, p->plane);
    t_vector_2d ray_dir_right = ft_vector_add(p->dir, p->plane);
    t_vector_2d floor_step = ft_vector_div(ft_vector_scale(ft_vector_sub(ray_dir_right, ray_dir_left), row_distance), (t_vector_2d){data->window->width, data->window->width});
    t_vector_2d floor = ft_vector_add(p->pos, ft_vector_scale(ray_dir_left, row_distance));

    for (int x = 0; x < data->window->width; ++x) {
        t_coordinate cell = {(int)floor.x, (int)floor.y};
        t_coordinate texture = {
            (int)(TEX_WIDTH_FLOOR * (floor.x - cell.x)) & (TEX_WIDTH_FLOOR - 1),
            (int)(TEX_HEIGHT_FLOOR * (floor.y - cell.y)) & (TEX_HEIGHT_FLOOR - 1)
        };
        uint32_t floorColor = get_pixel(data->texture[6], texture.x, texture.y);
        uint32_t ceilingColor = get_pixel(data->texture[5], texture.x, texture.y); // For simplicity, using the same texture for ceiling. Adjust if different texture is needed.

        mlx_put_pixel(data->window->image, x, y, floorColor);
        mlx_put_pixel(data->window->image, x, data->window->height - y - 1, ceilingColor);

        floor = ft_vector_add(floor, floor_step);
    }
}
