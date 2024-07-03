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
    // mlx_set_setting(MLX_STRETCH_IMAGE, 1);
    t_data *data = static_data();
    draw_rays();

    mlx_image_to_window(data->window->mlx, data->window->image, 0, 0);
    mlx_loop_hook(data->window->mlx, wasd_key_input, data);


    mlx_set_cursor_mode(data->window->mlx, MLX_MOUSE_HIDDEN);
    mlx_set_mouse_pos(data->window->mlx, WINDOW_H_INIT/2, WINDOW_W_INIT/2);
    mlx_cursor_hook(data->window->mlx, &mouse_move_callback, data);
    mlx_mouse_hook(data->window->mlx, mouse_click_handler, data);
    mlx_key_hook(data->window->mlx, key_handler, data);
    mlx_resize_hook(data->window->mlx, resize_handler, data->window);
    mlx_loop(data->window->mlx);
    mlx_terminate(data->window->mlx);
    return 0;
}
