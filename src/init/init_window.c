/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:12:47 by jmoritz           #+#    #+#             */
/*   Updated: 2024/06/20 19:14:01 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_window	*init_window()
{
    t_window *window;
    window = malloc(sizeof(t_window));
    window->mlx = mlx_init(WINDOW_W_INIT, WINDOW_H_INIT, "Cub3D", true);
    if (window->mlx == NULL) {
        printf("Error: Malloc failed\n");
        exit(1);
    }
    window->image = mlx_new_image(window->mlx, WINDOW_W_INIT, WINDOW_H_INIT);
    if (window->image == NULL) {
        printf("Error: Malloc failed\n");
        exit(1);
    }
    window->width = WINDOW_W_INIT;
    window->height = WINDOW_H_INIT;

    return window;
}