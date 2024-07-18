/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wasd_key_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 08:58:01 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/18 14:12:34 by lzipp            ###   ########.fr       */
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

//TODO: remove this
static t_sprite_data g_sprite = {.pos = {0, 0}, .texture = 0, .last_animation_change = 0, .animation_speed = 0};
static int g_sprite_initialized = 0;

void	wasd_key_input(void *data)
{
	t_data	*d = data;
	mlx_t *mlx = d->window->mlx;

	//TODO: remove this
	if (!g_sprite_initialized) {
		g_sprite.pos = (t_vector_2d){2, 2};
		g_sprite.texture = 0;
		g_sprite.last_animation_change = 0;
		g_sprite.animation_speed = 0.2;
		g_sprite_initialized = 1;
	}

	if (mlx_is_key_down(mlx, MLX_KEY_W) || mlx_is_key_down(mlx, MLX_KEY_A)
		|| mlx_is_key_down(mlx, MLX_KEY_S) || mlx_is_key_down(mlx, MLX_KEY_D))
		move_player(d);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		rotate_player(d, d->player.rot_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		rotate_player(d, -d->player.rot_speed);

	// make_window_black();
	draw_rays();
	draw_sprite(data, &g_sprite);
	draw_mini_map(data);
}

