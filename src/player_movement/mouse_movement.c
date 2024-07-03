/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:53:06 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/02 14:53:10 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void mouse_move_callback(double xpos, double ypos, void *param) {
    static double last_xpos = -1;
    t_data *data = (t_data *)param;
    (void)ypos;

    // Center of the window
    const int center_x = data->window->height / 2;
    const int center_y = data->window->width / 2;

    if (last_xpos == -1) {
        last_xpos = xpos;
        return;
    }

    const double delta_x = xpos - last_xpos;
    last_xpos = xpos;

    // Adjust the sensitivity as needed
    const double sensitivity = 0.001;
    const double angle = delta_x * sensitivity;

    rotate_player(data, -angle);

    // Reset the mouse position to the center of the window
    mlx_set_mouse_pos(data->window->mlx, center_x, center_y);
    last_xpos = center_x;  // Reset last_xpos to center_x to avoid large jumps
}