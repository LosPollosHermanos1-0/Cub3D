/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wasd_key_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 08:58:01 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/25 14:47:42 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	make_window_black(void)
{
	t_data	*data;
	int		x;
	int		y;

	data = static_data();
	y = -1;
	while (++y < data->window->height)
	{
		x = -1;
		while (x < data->window->width)
		{
			mlx_put_pixel(data->window->image, x, y, 0x00000000);
		}
	}
}

void	wasd_key_input(void *data)
{
	t_data		*d;
	mlx_t		*mlx;
	int			i;

	d = (t_data *)data;
	mlx = d->window->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_W) || mlx_is_key_down(mlx, MLX_KEY_A)
		|| mlx_is_key_down(mlx, MLX_KEY_S) || mlx_is_key_down(mlx, MLX_KEY_D))
		move_player(d);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		rotate_player(d, d->player.rot_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		rotate_player(d, -d->player.rot_speed);
	draw_rays();
	sort_sprites(d);
	i = -1;
	while (++i < d->opponent_count)
	{
		draw_sprite(data, &d->sprites[i]);
		move_opponent(d, &d->sprites[i]);
	}
	draw_mini_map(d);
	draw_door_icon(d);
}
