/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:24:54 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/03 13:25:00 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	resize_handler(int32_t width, int32_t height, void* win)
{
    t_window *window = win;
    mlx_delete_image(window->mlx, window->image);
    window->width = width;
    window->height = height;
    window->image = mlx_new_image(window->mlx, window->width, window->height);
    mlx_image_to_window(window->mlx, window->image, 0,0);
    if (window->image == NULL)
    {
        printf("Error: Malloc failed\n");
        exit(1);
    }
}
