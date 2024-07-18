/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:08:21 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/18 15:33:36 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		make_mini_black(t_data *data);
static void		draw_walls(t_data *data);
static void		draw_player(t_data *data);

/**
 * Repeatedly draws background of minimap
 * @param data
 */
void	draw_mini_map(t_data *data)
{
	make_mini_black(data);
	draw_walls(data);
	draw_player(data);
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

/**
 * Draws walls on minimap
 * @param data
 
 */
static void	draw_walls(t_data *data)
{
	;
}

/**
 * Draws player on minimap
 * @param data
 */
static void	draw_player(t_data *data)
{
	;
}
