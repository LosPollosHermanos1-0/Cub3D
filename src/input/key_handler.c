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
}
