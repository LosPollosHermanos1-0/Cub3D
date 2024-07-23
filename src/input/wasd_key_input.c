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
	for (int y = 0; y < data->window->height; ++y) {
		for (int x = 0; x < data->window->width; ++x) {
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
		move_player(d);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		rotate_player(d, d->player.rot_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		rotate_player(d, -d->player.rot_speed);

	draw_rays();
	for (int i = 0; i < d->opponent_count; ++i) {
		draw_sprite(data, &d->sprites[i]);
		move_opponent(d, &d->sprites[i]);
	}
	draw_mini_map(d);
	draw_door_icon(d);
}

