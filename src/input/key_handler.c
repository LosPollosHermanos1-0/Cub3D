/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:10:01 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/02 19:20:34 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_handler(const mlx_key_data_t keydata, void *data)
{
	(void)data;
	if (keydata.key == MLX_KEY_ESCAPE)
		ft_exit();
}