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

int main()
{
    t_data *data = static_data();
    draw_rays();

    // draw_line(data->window->image, (t_vector_2d){0, 0}, (t_vector_2d){100, 100}, 0x00FF00FF);
    // draw_line_vector(data->window->image, (t_vector_2d){400, 400}, (t_vector_2d){90, 100}, 0x00FF00FF);
    // draw_line_vector(data->window->image, (t_vector_2d){400, 400}, (t_vector_2d){0, 100}, 0x00FF00FF);
    // draw_line_vector(data->window->image, (t_vector_2d){500, 400}, (t_vector_2d){180, -100}, 0x00FF00FF);
    mlx_image_to_window(data->window->mlx, data->window->image, 0, 0);
    // mlx_key_hook(data->window->mlx, arrow_key_hook, data);
    mlx_loop_hook(data->window->mlx, wasd_key_input, data);
    mlx_set_cursor_mode(data->window->mlx, MLX_MOUSE_HIDDEN);
    mlx_set_mouse_pos(data->window->mlx, WINDOW_H/2, WINDOW_W/2);
    mlx_cursor_hook(data->window->mlx, &mouse_move_callback, data);
    mlx_loop(data->window->mlx);
    mlx_terminate(data->window->mlx);
    return 0;
}