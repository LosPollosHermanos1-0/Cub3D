/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:08:21 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/18 15:11:28 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void make_mini_black(t_data *data);

/**
 * Repeatedly draws background of minimap
 * @param data
 */
void	draw_mini_map(t_data *data)
{
	make_mini_black(data);
}

/**
 * Fills minimap with black color
 * @param data
 */
static void make_mini_black(t_data *data)
{
	int	y;
	int	x;

	y = -1;
	while (++y < data->window->mini_height) {
		x = -1;
		while (++x < data->window->mini_width) {
			mlx_put_pixel(data->window->mini_image, x, y, 0x000000FF);
		}
	}
}

// void	draw_lines(t_data *data)
// {
// 	;
// }
