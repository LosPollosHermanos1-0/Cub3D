/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:08:21 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/18 17:56:18 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		make_mini_black(t_data *data);
static void		draw_mini_map_elements(t_data *data, double scale);
static void		draw_mini_player(t_data *data);
static uint32_t	get_color(t_data *data, int x, int y);
static void		draw_to_scale(t_data *data, double scale);

/**
 * Repeatedly draws background of minimap
 * @param data
 */
void	draw_mini_map(t_data *data)
{
	double		scale1;
	double		scale2;

	scale1 = data->window->mini_height / data->map->height;
	scale2 = data->window->mini_width / data->map->width;
	if (scale1 > scale2)
		scale1 = scale2;
	printf("scale1: %f\n", scale1);
	make_mini_black(data);
	draw_mini_map_elements(data, scale1);
	draw_mini_player(data);
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
	while (++y < data->window->mini_height)
	{
		x = -1;
		while (++x < data->window->mini_width)
		{
			mlx_put_pixel(data->window->mini_image, x, y, 0x000000FF);
		}
	}
}

/**
 * Draws floor, walls, doors and other elements on minimap except player
 * @param data
 */
static void	draw_mini_map_elements(t_data *data, double scale)
{
	int	y;
	int	x;

	y = -1;
	while (++y < data->window->mini_height)
	{
		x = -1;
		while (++x < data->window->mini_width)
			draw_to_scale(data, scale);
	}
}

/**
 * Draws player on minimap
 * @param data
 */
static void	draw_mini_player(t_data *data)
{
	uint32_t	pos_y;
	uint32_t	pos_x;
	
	pos_y = data->player.pos.y;
	pos_x = data->player.pos.x;
}

// static void	draw_minimap_to_scale(mlx_image_t *img, int pos[2], int size,
// 		int color)
static void	draw_to_scale(t_data *data, double scale)
{
	int		i;
	int		j;

	i = -1;
	while (++i < scale)
	{
		j = -1;
		while (++j < scale)
		{
			if (data->player.pos.x * scale + i >= 0 && data->player.pos.x * scale + i < data->map->width
				&& data->player.pos.y * scale + j >= 0 && data->player.pos.y * scale + j < data->map->height)
				mlx_put_pixel(data->window->mini_image, data->player.pos.x * scale + i, data->player.pos.y * scale + j, get_color(data, data->player.pos.x * scale + i, data->player.pos.y * scale + j));
		}
	}
}

/**
 * Returns color of element on minimap
 * @param data
 */
static uint32_t	get_color(t_data *data, int x, int y)
{
	// everything outside of map
	if ((x < 0 || y < 0 || x >= data->map->width
			|| y >= data->map->height)
		|| data->map->map[y][x] == END
		|| data->map->map[y][x] == OUTSIDE)
		return (0x000000FF);
	// walls
	else if (data->map->map[y][x] == WALL)
		return (0x0000FFFF);
	// doors
	else if (data->map->map[y][x] == DOOR)
		return (0xFFFFFFFF);
	// else if (data->map->map[y][x] == OPEN_DOOR)
	// 	return (0xAA00AAFF);
	// floor
	return (0xFF0000FF);
}
