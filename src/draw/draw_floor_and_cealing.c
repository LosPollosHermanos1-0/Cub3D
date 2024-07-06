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

uint32_t blend_color(uint32_t originalColor, float blendFactor) {
    uint8_t r = (originalColor >> 24) & 0xFF;
    uint8_t g = (originalColor >> 16) & 0xFF;
    uint8_t b = (originalColor >> 8) & 0xFF;
    // Darken the color based on blendFactor
    r *= (1 - blendFactor);
    g *= (1 - blendFactor);
    b *= (1 - blendFactor);
    return (r << 24) | (g << 16) | (b << 8) | 0xFF; // Assuming alpha is always 255
}

uint32_t blend_two_colors(uint32_t color1, uint32_t color2, float blendFactor) {
    // Extracting RGB components from both colors
    uint8_t r1 = (color1 >> 24) & 0xFF;
    uint8_t g1 = (color1 >> 16) & 0xFF;
    uint8_t b1 = (color1 >> 8) & 0xFF;

    uint8_t r2 = (color2 >> 24) & 0xFF;
    uint8_t g2 = (color2 >> 16) & 0xFF;
    uint8_t b2 = (color2 >> 8) & 0xFF;

    // Linearly interpolating each component
    uint8_t rResult = (uint8_t)(r1 + (r2 - r1) * blendFactor);
    uint8_t gResult = (uint8_t)(g1 + (g2 - g1) * blendFactor);
    uint8_t bResult = (uint8_t)(b1 + (b2 - b1) * blendFactor);

    // Combining the components back into a single uint32_t color
    return (rResult << 24) | (gResult << 16) | (bResult << 8) | 0xFF; // Assuming alpha is always 255
}

bool is_in_circle(t_vector_2d center, double radius, t_vector_2d point) {
    return (point.x - center.x) * (point.x - center.x) + (point.y - center.y) * (point.y - center.y) <= radius * radius;
}

inline void draw_floor_and_ceiling(t_data *data, int y) {
    const t_player p = data->player;
    double half_height = data->window->height / 2.0;
    double position = y - half_height;
    double row_distance = half_height / position;

    t_vector_2d ray_dir_left = ft_vector_sub(p.dir, p.plane);
    t_vector_2d ray_dir_right = ft_vector_add(p.dir, p.plane);
    t_vector_2d floor_step = ft_vector_div(ft_vector_scale(ft_vector_sub(ray_dir_right, ray_dir_left), row_distance), (t_vector_2d){data->window->width, data->window->width});
    t_vector_2d floor = ft_vector_add(p.pos, ft_vector_scale(ray_dir_left, row_distance));

    for (int x = 0; x < data->window->width; ++x) {
        t_coordinate cell = {(int)floor.x, (int)floor.y};
        t_coordinate texture = {
            (int)(TEX_WIDTH_FLOOR * (floor.x - cell.x)) & (TEX_WIDTH_FLOOR - 1),
            (int)(TEX_HEIGHT_FLOOR * (floor.y - cell.y)) & (TEX_HEIGHT_FLOOR - 1)
        };
        uint32_t floorColor = get_pixel(data->texture[1], texture.x, texture.y);
        // printf("floor.x: %f, floor.y: %f\n", floor.x, floor.y);

        if (is_in_circle((t_vector_2d){20,12}, 0.5, (t_vector_2d){floor.x, floor.y})) {
            floorColor = blend_two_colors(floorColor, (255 << 24) | (255 << 16) | (0 << 8) | 0xFF, 0.1);
        }
        uint32_t ceilingColor = get_pixel(data->texture[1], texture.x, texture.y); // For simplicity, using the same texture for ceiling. Adjust if different texture is needed.

        mlx_put_pixel(data->window->image, x, y, floorColor);
        mlx_put_pixel(data->window->image, x, data->window->height - y - 1, ceilingColor);

        floor = ft_vector_add(floor, floor_step);
    }
}
