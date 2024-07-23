/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:08:21 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/23 09:05:26 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		draw_mini_map_element(t_data **data, int map_x, int map_y,
					double scale);
static void		ft_draw_mini_player(t_data **data, double scale);
static uint32_t	get_color(t_data *data, int x, int y);
static bool		ft_is_point_in_triangle(t_vector_2d *point, t_vector_2d *a,
					t_vector_2d *b, t_vector_2d *c);

/**
 * Repeatedly draws minimap
 * @param data
 */
void	draw_mini_map(t_data **data)
{
	double		scale;
	double		scale2;
	int			x;
	int			y;

	scale = (*data)->window->mini_height / (*data)->map->height;
	scale2 = (*data)->window->mini_width / (*data)->map->width;
	if (scale > scale2)
		scale = scale2;
	y = -1;
	while (++y < (*data)->map->height)
	{
		x = -1;
		while (x < (*data)->map->width && (*data)->map->map[y][++x] != END)
			draw_mini_map_element(data, x, y, scale);
	}
	ft_draw_mini_player(data, scale);
}

/**
 * Draws static elements on minimap
 * @param data app data
 * @param map_x x coordinate of element on map
 * @param map_y y coordinate of element on map
 * @param scale scale of minimap
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
 * @param scale
 */
static void	ft_draw_mini_player(t_data **data, double scale)
{
	t_vector_2d	player[3];
	int			x;
	int			y;

	player[0] = (t_vector_2d){(*data)->player.pos.x * scale
		+ 2 * (*data)->player.dir.x * scale / 2,
		(*data)->player.pos.y * scale + 2 * (*data)->player.dir.y * scale / 2};
	player[1] = (t_vector_2d){(*data)->player.pos.x * scale
		- (*data)->player.dir.y * scale / 3,
		(*data)->player.pos.y * scale + (*data)->player.dir.x * scale / 3};
	player[2] = (t_vector_2d){(*data)->player.pos.x * scale
		+ (*data)->player.dir.y * scale / 3,
		(*data)->player.pos.y * scale - (*data)->player.dir.x * scale / 3};
	y = -1;
	while (++y < (*data)->window->mini_height)
	{
		x = -1;
		while (++x < (*data)->window->mini_width)
			if (x >= 0 && x < (*data)->window->mini_width && y >= 0
				&& y < (*data)->window->mini_height
				&& ft_is_point_in_triangle(&(t_vector_2d){x, y}, &player[0],
				&player[1], &player[2]))
				mlx_put_pixel((*data)->window->mini_image, y, x, 0xAAFFFFFF);
	}
}

/**
 * Checks if point is in player
 * @param point point to check
 * @param a corner a of player
 * @param b corner b of player
 * @param c corner c of player
 */
static bool	ft_is_point_in_triangle(t_vector_2d *point, t_vector_2d *a,
		t_vector_2d *b, t_vector_2d *c)
{
	double	denominator;
	double	alpha;
	double	beta;
	double	gamma;

	denominator = ((b->y - c->y) * (a->x - c->x)
			+ (c->x - b->x) * (a->y - c->y));
	alpha = ((b->y - c->y) * (point->x - c->x)
			+ (c->x - b->x) * (point->y - c->y)) / denominator;
	beta = ((c->y - a->y) * (point->x - c->x)
			+ (a->x - c->x) * (point->y - c->y)) / denominator;
	gamma = 1.0 - alpha - beta;
	return ((alpha > 0) && (beta > 0) && (gamma > 0));
}

/**
 * Returns color of element on minimap
 * @param data
 * @param x
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
	// else if (data->map->map[y][x] == DOOR_CLOSED) //newer
	else if (data->map->map[y][x] == DOOR_CLOSED)
		{printf("door\n"); return (0xA52A2AFF);}
	// sprites
	else if (data->map->map[y][x] == SPRITE)
		return (0xFFFF0000);
	// else if (data->map->map[y][x] ==DOOR_OPEN)
	// 	return (0xAA00AAFF);
	// floor
	return (0x000000FF);
}
