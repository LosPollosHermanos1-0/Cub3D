/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:42:07 by jmoritz           #+#    #+#             */
/*   Updated: 2024/06/26 11:43:18 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void draw_rays() {
    t_data *data = static_data();

    for (int x = 0; x < WINDOW_W; ++x) {
        double camera_x = 2 * x / (double)WINDOW_W - 1;
        t_vector_2d ray_dir = ft_vector_init(data->player->dir.x + data->player->plane.x * camera_x,
                                             data->player->dir.y + data->player->plane.y * camera_x);
        ray_dir = ft_vector_scale(ray_dir, 100);
        draw_line_vector(data->window->image, data->player->pos, ray_dir, 0x00FF00FF);
    }
}

int main()
{
    t_data *data = static_data();
    draw_rays();

    // draw_line(data->window->image, (t_vector_2d){0, 0}, (t_vector_2d){100, 100}, 0x00FF00FF);
    // draw_line_vector(data->window->image, (t_vector_2d){400, 400}, (t_vector_2d){90, 100}, 0x00FF00FF);
    // draw_line_vector(data->window->image, (t_vector_2d){400, 400}, (t_vector_2d){0, 100}, 0x00FF00FF);
    // draw_line_vector(data->window->image, (t_vector_2d){500, 400}, (t_vector_2d){180, -100}, 0x00FF00FF);
    mlx_image_to_window(data->window->mlx, data->window->image, 0, 0);
    mlx_loop(data->window->mlx);
    mlx_terminate(data->window->mlx);
    return 0;
}