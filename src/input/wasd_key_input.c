/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wasd_key_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 08:58:01 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/02 08:58:07 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void make_window_black() {
	t_data *data = static_data();
	for (int y = 0; y < WINDOW_H; ++y) {
		for (int x = 0; x < WINDOW_W; ++x) {
			mlx_put_pixel(data->window->image,  x, y, 0x00000000);
		}
	}
}

void	wasd_key_input(void *data)
{
	t_data	*d = data;
	mlx_t *mlx = d->window->mlx;

	if (mlx_is_key_down(mlx, MLX_KEY_W) || mlx_is_key_down(mlx, MLX_KEY_A)
		|| mlx_is_key_down(mlx, MLX_KEY_S) || mlx_is_key_down(mlx, MLX_KEY_D))
	{
		printf("key pressed\n");
		move_player(d);
	}
	make_window_black();
	draw_rays();
}
