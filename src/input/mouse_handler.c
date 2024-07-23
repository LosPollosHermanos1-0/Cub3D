/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:34:36 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/23 09:08:42 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	center_mouse(const t_data *data)
{
	const int	center_x = data->window->width / 2;
	const int	center_y = data->window->height / 2;

	mlx_set_mouse_pos(data->window->mlx, center_x, center_y);
}

void	toogle_mouselock_and_visability(t_data *data)
{
	data->flags ^= FLAG_MOUSE_LOCKED;
	if (data->flags & FLAG_MOUSE_LOCKED)
	{
		center_mouse(data);
		set_last_xpos(-1);
		mlx_set_cursor_mode(data->window->mlx, MLX_MOUSE_HIDDEN);
	}
	else
		mlx_set_cursor_mode(data->window->mlx, MLX_MOUSE_NORMAL);
}

void	mouse_move_callback(const double xpos, const double ypos, void *param)
{
	rotate_player_mouse(xpos, ypos, param);
}

void	mouse_click_handler(const mouse_key_t button, const action_t action,
		const modifier_key_t mods, void *p)
{
	const t_data	*data = p;

	(void)mods;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		if (!(data->flags & FLAG_MOUSE_LOCKED))
			toogle_mouselock_and_visability(p);
}
