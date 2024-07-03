/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:41:42 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/03 02:42:09 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_wall_intersection_piont(const t_data *data,
        const t_raycast_data *rd, t_wall_rendering_data *wrd)
{
    if (rd->side == 0)
        wrd->wall_x = data->player->pos.y + rd->perp_wall_dist * rd->ray_dir.y;
    else
        wrd->wall_x = data->player->pos.x + rd->perp_wall_dist * rd->ray_dir.x;
    wrd->wall_x -= floor(wrd->wall_x);
}

void	adjust_texture_x_coordinate(const t_raycast_data *rd,
        t_wall_rendering_data *wrd)
{
    wrd->tex_x = (int)(wrd->wall_x * (double)TEX_WIDTH);
    if (rd->side == 0 && rd->ray_dir.x > 0)
        wrd->tex_x = TEX_WIDTH - wrd->tex_x - 1;
    if (rd->side == 1 && rd->ray_dir.y < 0)
        wrd->tex_x = TEX_WIDTH - wrd->tex_x - 1;
}

void	calculate_wall_projection_bounds(const t_raycast_data *rd,
        t_wall_rendering_data *wrd)
{
    wrd->draw_start = -rd->line_height / 2 + WINDOW_H / 2;
    if (wrd->draw_start < 0)
        wrd->draw_start = 0;
    wrd->draw_end = rd->line_height / 2 + WINDOW_H / 2;
    if (wrd->draw_end >= WINDOW_H)
        wrd->draw_end = WINDOW_H - 1;
}

void	draw_walls(const t_data *data, const t_raycast_data *rd, const int x)
{
    u_int32_t				color;
    t_wall_rendering_data	*wrd;

    wrd = malloc(sizeof(t_wall_rendering_data));
    wrd->tex_num = data->map->map[rd->map_x][rd->map_y] - 1;
    calculate_wall_intersection_piont(data, rd, wrd);
    adjust_texture_x_coordinate(rd, wrd);
    calculate_wall_projection_bounds(rd, wrd);
    wrd->step = 1.0 * TEX_HEIGHT / rd->line_height;
    wrd->tex_pos = (wrd->draw_start - WINDOW_H / 2 + rd->line_height / 2)
        * wrd->step;
    for (int y = wrd->draw_start; y < wrd->draw_end; y++)
    {
        wrd->tex_y = (int)wrd->tex_pos & (TEX_HEIGHT - 1);
        wrd->tex_pos += wrd->step;
        color = get_pixel(data->texture[wrd->tex_num], wrd->tex_x, wrd->tex_y);
        if (rd->side == 1)
            color = (color >> 1) & 8355711;
        mlx_put_pixel(data->window->image, x, y, color);
    }
    free(wrd);
}