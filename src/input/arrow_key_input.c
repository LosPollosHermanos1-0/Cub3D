/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_key_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:35:25 by jmoritz           #+#    #+#             */
/*   Updated: 2024/06/27 14:35:28 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


#define mapWidth 24
#define mapHeight 24

uint32_t create_color(const uint8_t alpha, const uint8_t red, const uint8_t green, const uint8_t blue) {
    return (red << 24) | (green << 16) | (blue << 8) | alpha;
}

void set_color_based_on_map(const int number, uint32_t *color) {
    switch (number) {
        case 1:
            *color = create_color(0xFF, 0xFF, 0x00, 0x00); // Red
        break;
        case 2:
            *color = create_color(0xFF, 0x00, 0xFF, 0x00); // Green
        break;
        case 3:
            *color = create_color(0xFF, 0x00, 0x00, 0xFF); // Blue
        break;
        case 4:
            *color = create_color(0xFF, 0xFF, 0xFF, 0x00); // Yellow
        break;
        default:
            *color = create_color(0xFF, 0xFF, 0xFF, 0xFF); // White
        break;
    }
}

int worldMap[mapWidth][mapHeight]=
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void make_window_black() {
    t_data *data = static_data();
    for (int y = 0; y < WINDOW_H; ++y) {
        for (int x = 0; x < WINDOW_W; ++x) {
            mlx_put_pixel(data->window->image,  x, y, 0x00000000);
        }
    }
}

void draw_grid() {
    t_data *data = static_data();
    for (int y = 0; y < WINDOW_H; y += 20) {
        for (int x = 0; x < WINDOW_W; x += 20) {
            mlx_put_pixel(data->window->image, x, y, 0x00FF00FF);
        }
    }
}

t_vector_2d calculate_delta_dist(t_vector_2d ray_dir) {
    t_vector_2d delta_dist;

    if (ray_dir.x != 0) {
        delta_dist.x = fabs(1 / ray_dir.x);
    } else {
        // Handle the case where ray_dir.x is zero
        delta_dist.x = INFINITY; // or some large number, or handle as needed
    }

    if (ray_dir.y != 0) {
        delta_dist.y = fabs(1 / ray_dir.y);
    } else {
        // Handle the case where ray_dir.y is zero
        delta_dist.y = INFINITY; // or some large number, or handle as needed
    }

    return delta_dist;
}

void draw_rays() {
    t_data *data = static_data();

    for (int x = 0; x < WINDOW_W; ++x) {
        double camera_x = 2 * x / (double)WINDOW_W - 1;
        t_vector_2d ray_dir = ft_vector_init(data->player->dir.x + data->player->plane.x * camera_x,
                                             data->player->dir.y + data->player->plane.y * camera_x);
        int map_x = (int)data->player->pos.x;
        int map_y = (int)data->player->pos.y;

        t_vector_2d side_dist;
        t_vector_2d delta_dist = calculate_delta_dist(ray_dir);
        double perp_wall_dist;

        int step_x;
        int step_y;

        int hit = 0;
        int side = 0;

        if (ray_dir.x < 0) {
            step_x = -1;
            side_dist.x = (data->player->pos.x - map_x) * delta_dist.x;
        } else {
            step_x = 1;
            side_dist.x = (map_x + 1.0 - data->player->pos.x) * delta_dist.x;
        }
        if (ray_dir.y < 0) {
            step_y = -1;
            side_dist.y = (data->player->pos.y - map_y) * delta_dist.y;
        } else {
            step_y = 1;
            side_dist.y = (map_y + 1.0 - data->player->pos.y) * delta_dist.y;
        }

        while (hit == 0) {
            if (side_dist.x < side_dist.y) {
                side_dist.x += delta_dist.x;
                map_x += step_x;
                side = 0;
            } else {
                side_dist.y += delta_dist.y;
                map_y += step_y;
                side = 1;
            }
            if (worldMap[map_x][map_y] > 0) {
                hit = 1;
            }
        }

        if (side == 0) {
            perp_wall_dist = (map_x - data->player->pos.x + (1 - step_x) / 2) / ray_dir.x;
        } else {
            perp_wall_dist = (map_y - data->player->pos.y + (1 - step_y) / 2) / ray_dir.y;
        }

        int line_height = (int)(WINDOW_H / perp_wall_dist);

        u_int32_t color;
        set_color_based_on_map(worldMap[map_x][map_y], &color);

        t_vector_2d start = ft_vector_init(x, WINDOW_H / 2 - line_height / 2);
        t_vector_2d end = ft_vector_init(x, WINDOW_H / 2 + line_height / 2);
        draw_line(data->window->image, start, end, color);
    }
}

void arrow_key_hook(const mlx_key_data_t keydata, void* param) {
    t_data *data = param;
    if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS) {
        data->player->dir = ft_vector_rotate(data->player->dir, -0.1);
        data->player->plane = ft_vector_rotate(data->player->plane, -0.1);
    }
    if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS) {
        data->player->dir = ft_vector_rotate(data->player->dir, 0.1);
        data->player->plane = ft_vector_rotate(data->player->plane, 0.1);
    }
    if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS) {
        if (worldMap[(int)(data->player->pos.x + data->player->dir.x * 0.1)][(int)data->player->pos.y] == 0) {
            data->player->pos = ft_vector_add(data->player->pos, ft_vector_scale(data->player->dir, 0.1));
        }
        if (worldMap[(int)data->player->pos.x][(int)(data->player->pos.y + data->player->dir.y * 0.1)] == 0) {
            data->player->pos = ft_vector_add(data->player->pos, ft_vector_scale(data->player->dir, 0.1));
        }
    }
    make_window_black();
    draw_rays();
}