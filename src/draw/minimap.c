/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:08:21 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/19 13:22:20 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		draw_mini_map_element(t_data **data, int map_x, int map_y,
					double scale);
static void		draw_mini_player(t_data **data, double scale);
static uint32_t	get_color(t_data *data, int x, int y);

/**
 * Repeatedly draws minimap
 * @param data
 */
void	draw_mini_map(t_data **data)
{
	double		scale1;
	double		scale2;
	int			x;
	int			y;

	scale1 = (*data)->window->mini_height / (*data)->map->height;
	scale2 = (*data)->window->mini_width / (*data)->map->width;
	if (scale1 > scale2)
		scale1 = scale2;
	y = -1;
	while (++y < (*data)->map->height)
	{
		x = -1;
		while (x < (*data)->map->width && (*data)->map->map[y][++x] != END)
		{
			printf("map height && width = %d, %d\n", (*data)->map->height, (*data)->map->width);
			printf("at map[%d][%d] = %d\n", y, x, (*data)->map->map[y][x]);
			printf("player pos y,x = %d,%d\n", (uint32_t)(*data)->player.pos.x, (uint32_t)(*data)->player.pos.y);
			draw_mini_map_element(data, x, y, scale1);
			if ((uint32_t)round((*data)->player.pos.y) == (uint32_t)x && (uint32_t)round((*data)->player.pos.x) == (uint32_t)y)
				draw_mini_player(data, scale1);
			// else
		}
	}
}

/**
 * Draws static elements on minimap
 * @param data
 */
static void	draw_mini_map_element(t_data **data, int map_x, int map_y,
				double scale)
{
	uint32_t	color;
	int			pixel_x;
	int			pixel_y;

	color = get_color((*data), map_x, map_y);
	pixel_y = -1;
	while (++pixel_y < scale)
	{
		pixel_x = -1;
		while (++pixel_x < scale)
		{
			if (map_x * scale + pixel_x >= 0
				&& map_x * scale + pixel_x < (*data)->map->width * scale
				&& map_y * scale + pixel_y >= 0
				&& map_y * scale + pixel_y < (*data)->map->height * scale)
				mlx_put_pixel((*data)->window->mini_image,
					map_x * scale + pixel_x, map_y * scale + pixel_y, color);
		}
	}
}

/**
 * Draws player on minimap
 * @param data
 */
static void	draw_mini_player(t_data **data, double scale)
{
	uint32_t	pos_y;
	uint32_t	pos_x;
	int			pixel_y;
	int			pixel_x;

	pos_y = (*data)->player.pos.y;
	pos_x = (*data)->player.pos.x;
	pixel_y = -1;
	while (++pixel_y < scale)
	{
		pixel_x = -1;
		while (++pixel_x < scale)
		{
			if (pos_y * scale + pixel_x >= 0
				&& pos_y * scale + pixel_x < (*data)->map->width * scale
				&& pos_x * scale + pixel_y >= 0
				&& pos_x * scale + pixel_y < (*data)->map->height * scale)
				// mlx_put_pixel((*data)->window->mini_image,
				// 	pos_x * scale + pixel_x, pos_y * scale + pixel_y, 0xAAFFFFFF);
				mlx_put_pixel((*data)->window->mini_image,
					pos_y * scale + pixel_y, pos_x * scale + pixel_x, 0xAAFFFFFF);
		}
	}
}

/**
 * Returns color of element on minimap
 * @param data
 */
static uint32_t	get_color(t_data *data, int x, int y)
{
	// everything that is not an element
	if ((x < 0 || y < 0 || x >= data->map->width
			|| y >= data->map->height)
		|| data->map->map[y][x] == EMPTY
		|| data->map->map[y][x] == END
		|| data->map->map[y][x] == OUTSIDE)
		return (0x000000FF);
	// walls
	else if (data->map->map[y][x] == WALL)
		return (0xFFFFFFFF);
	// doors
	else if (data->map->map[y][x] == DOOR)
		return (0xFFA52A2A);
	// sprites
	else if (data->map->map[y][x] == SPRITE)
		return (0xFFFF0000);
	// else if (data->map->map[y][x] == OPEN_DOOR)
	// 	return (0xAA00AAFF);
	// floor
	return (0x000000FF);
}
