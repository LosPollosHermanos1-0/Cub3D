/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:08:21 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/18 14:11:16 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Repeatedly draws background of minimap
 * @param data
 */
inline void	draw_mini_map(t_data *data)
{
	mlx_clear_image(data->window->mlx, data->window->mini_image);
	mlx_draw_rect(data->window->mini_image, 0, 0, data->window->mini_width,
		data->window->mini_height, 0x000000);
}
