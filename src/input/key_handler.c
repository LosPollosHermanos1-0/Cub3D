/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:10:01 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/03 17:12:51 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_handler(const mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		ft_exit();
	if (keydata.key == MLX_KEY_LEFT_CONTROL && keydata.action == MLX_PRESS)
	{
		toogle_mouselock_and_visability(data);
	}
	if(keydata.key == MLX_KEY_F && keydata.action == MLX_PRESS) {
		if (data->flags & FLAG_FACING_OPEN_DOOR) {
			data->map->map[(int)data->last_faced_closed_door.x][(int)data->last_faced_closed_door.y] = DOOR_CLOSED;
			// printf("Door closed\n");
			// data->flags &= ~FLAG_FACING_OPEN_DOOR;
		}
		else if (data->flags & FLAG_FACING_CLOSED_DOOR) {
			data->map->map[(int)data->last_faced_closed_door.x][(int)data->last_faced_closed_door.y] = DOOR_OPEN;
			// printf("Door opened\n");
			// data->flags &= ~FLAG_FACING_CLOSED_DOOR;
		}
	}
}
