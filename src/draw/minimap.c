/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:08:21 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/22 20:34:27 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		draw_mini_map_element(t_data **data, int map_x, int map_y,
					double scale);
// static void		draw_mini_player(t_data **data, double scale);
static void		ft_draw_mini_player(t_data **data, double scale);
static uint32_t	get_color(t_data *data, int x, int y);
// void	draw_mini_line(t_data *data, double x_coord, double y_coord);
static bool	is_point_in_triangle(t_vector_2d point, t_vector_2d a, t_vector_2d b,
		t_vector_2d c);

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
			// printf("map height && width = %d, %d\n", (*data)->map->height, (*data)->map->width);
			printf("at map[%d][%d] = %d\n", y, x, (*data)->map->map[y][x]);
			printf("player pos y,x = %d,%d\n", (uint32_t)(*data)->player.pos.x, (uint32_t)(*data)->player.pos.y);
			draw_mini_map_element(data, x, y, scale1);
			// if ((int)((*data)->player.pos.y) == (int)x && (int)((*data)->player.pos.x) == (int)y)
			// 	{printf("triggered\n"); draw_mini_player(data, scale1);}
			// else
		}
	}
	ft_draw_mini_player(data, scale1);
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
// static void	draw_mini_player(t_data **data, double scale)
// {
// 	uint32_t	pos_y;
// 	uint32_t	pos_x;
// 	int			pixel_y;
// 	int			pixel_x;

// 	pos_y = (*data)->player.pos.y;
// 	pos_x = (*data)->player.pos.x;
// 	pixel_y = -1;
// 	while (++pixel_y < scale)
// 	{
// 		pixel_x = -1;
// 		while (++pixel_x < scale)
// 		{
// 			if (pos_y * scale + pixel_x >= 0
// 				&& pos_y * scale + pixel_x < (*data)->map->width * scale
// 				&& pos_x * scale + pixel_y >= 0
// 				&& pos_x * scale + pixel_y < (*data)->map->height * scale
// 				&& is_point_in_triangle((t_vector_2d){pos_y * scale + pixel_x, pos_x * scale + pixel_y},
// 					(t_vector_2d){pos_y * scale, pos_x * scale},
// 					(t_vector_2d){pos_y * scale + scale, pos_x * scale},
// 					(t_vector_2d){pos_y * scale + scale / 2, pos_x * scale + scale}))
// 				mlx_put_pixel((*data)->window->mini_image,
// 					pos_y * scale + pixel_y, pos_x * scale + pixel_x, 0xAAFFFFFF);
// 		}
// 	}
// }

// static void	draw_mini_player(t_data **data, double scale)
// {
// 	double		pos_y;
// 	double		pos_x;
// 	int			pixel_y;
// 	int			pixel_x;

// 	pos_y = (*data)->player.pos.y;
// 	pos_x = (*data)->player.pos.x;
// 	printf("x, y = %f, %f\n", pos_x, pos_y);
// 	pixel_y = -1;
// 	while (++pixel_y < scale)
// 	{
// 		pixel_x = -1;
// 		while (++pixel_x < scale)
// 		{
// 			if (pos_y * scale + pixel_x >= 0
// 				&& pos_y * scale + pixel_x < (*data)->map->width * scale
// 				&& pos_x * scale + pixel_y >= 0
// 				&& pos_x * scale + pixel_y < (*data)->map->height * scale
// 				&& is_point_in_triangle((t_vector_2d){pos_y * scale + pixel_x, pos_x * scale + pixel_y},
// 					(t_vector_2d){pos_y + (*data)->player.dir.y * scale, pos_x + (*data)->player.dir.x * scale},
// 					(t_vector_2d){pos_y * scale + scale, pos_x * scale},
// 					(t_vector_2d){pos_y * scale + scale / 2, pos_x * scale + scale}))
// 				mlx_put_pixel((*data)->window->mini_image,
// 					pos_y * scale + pixel_y, pos_x * scale + pixel_x, 0xAAFFFFFF);
// 		}
// 	}
// }

static void	ft_draw_mini_player(t_data **data, double scale)
{
	t_vector_2d	triangle[3];
	triangle[0] = (t_vector_2d){(*data)->player.pos.x * scale + 2 * (*data)->player.dir.x * scale / 2, (*data)->player.pos.y * scale + 2 * (*data)->player.dir.y * scale/ 2};
	triangle[1] = (t_vector_2d){(*data)->player.pos.x * scale - (*data)->player.dir.y * scale / 3, (*data)->player.pos.y * scale + (*data)->player.dir.x * scale / 3}; // Adjusted for a better triangle shape
	triangle[2] = (t_vector_2d){(*data)->player.pos.x * scale + (*data)->player.dir.y * scale / 3, (*data)->player.pos.y * scale - (*data)->player.dir.x * scale / 3}; // Adjusted for a better triangle shape
	int x = 0;
	int y = 0;
	while (y < (*data)->window->mini_height)
	{
		x = 0;
		while (x < (*data)->window->mini_width)
		{
			if (x >= 0 && x < (*data)->window->mini_width && y >= 0 && y < (*data)->window->mini_height
				&& is_point_in_triangle((t_vector_2d){x, y}, triangle[0], triangle[1], triangle[2]))
				mlx_put_pixel((*data)->window->mini_image, y, x, 0xAAFFFFFF);
			x++;
		}
		y++;
	}
}


static bool	is_point_in_triangle(t_vector_2d point, t_vector_2d a, t_vector_2d b,
		t_vector_2d c)
{
	double	denominator;
	double	alpha;
	double	beta;
	double	gamma;

	denominator = ((b.y - c.y) * (a.x - c.x) + (c.x - b.x) * (a.y - c.y));
	alpha = ((b.y - c.y) * (point.x - c.x) + (c.x - b.x) * (point.y - c.y))
		/ denominator;
	beta = ((c.y - a.y) * (point.x - c.x) + (a.x - c.x) * (point.y - c.y))
		/ denominator;
	gamma = 1.0 - alpha - beta;
	return ((alpha > 0) && (beta > 0) && (gamma > 0));
}

// static void	draw_triangle()

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
	// else if (data->map->map[y][x] == DOOR_CLOSED) //newer
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
