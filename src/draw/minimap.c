/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:08:21 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/22 13:32:48 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		draw_mini_map_element(t_data **data, int map_x, int map_y,
					double scale);
static void		draw_mini_player(t_data **data, double scale);
static uint32_t	get_color(t_data *data, int x, int y);
static void		draw_fov(t_data **data);
static void		clamp_to_mini_image(t_vector_2d *point);
static void		draw_mini_line(mlx_image_t *img, t_vector_2d start,
					t_vector_2d end, uint32_t color);
static void		do_mini_work(t_vector_2d start, t_vector_2d end,
					t_vector_2d *sign);
// void	draw_mini_line(t_data *data, double x_coord, double y_coord);

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
			// continue;
			// if ((uint32_t)round((*data)->player.pos.y) == (uint32_t)x && (uint32_t)round((*data)->player.pos.x) == (uint32_t)y)
			// 	{printf("triggered\n"); draw_mini_player(data, scale1);}
			if ((int)(*data)->player.pos.y == (int)x && (int)(*data)->player.pos.x == (int)y)
				{printf("triggered\n"); draw_mini_player(data, scale1);}
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
				mlx_put_pixel((*data)->window->mini_image,
					pos_y * scale + pixel_y, pos_x * scale + pixel_x, 0xAAFFFFFF);
		}
	}
	// return ;
	draw_fov(data);
	printf("after draw_fov\n");
}

static void	draw_fov(t_data **data)
{
	double		angle;
	t_player	player;
	t_vector_2d	start;
	t_vector_2d	left_end;
	t_vector_2d	right_end;

	player = (*data)->player;
	start = player.pos;
	angle = atan2f(player.dir.y, player.dir.x) - (double)(FOV / 2);
	left_end.x = start.x + cosf(angle) * 10;
	left_end.y = start.y + sinf(angle) * 10;
	angle = atan2f(player.dir.y, player.dir.x) + (double)(FOV / 2);
	right_end.x = start.x + cosf(angle) * 10;
	right_end.y = start.y + sinf(angle) * 10;
	printf("before drawing lines\n");
	printf("hey\n");
	draw_mini_line((*data)->window->mini_image, start, left_end, 0xFFFFFFFF);
	printf("first line done\n");
	draw_mini_line((*data)->window->mini_image, start, right_end, 0xFFFFFFFF);
	printf("second line done\n");
}

static void	draw_mini_line(mlx_image_t *img, t_vector_2d start, t_vector_2d end,
		uint32_t color)
{
	t_data		*data = static_data();
	t_vector_2d	delta;
	t_vector_2d	sign;
	t_vector_2d	cur;
	int			error;
	int			error2;

	printf("clamping 1\n");
	clamp_to_mini_image(&start);
	printf("clamping 2\n");
	clamp_to_mini_image(&end);

	delta = ft_vector_init(fabs(end.x - start.x), fabs(end.y - start.y));
	printf("before do_mini_work\n");
	do_mini_work(start, end, &sign);
	printf("before error\n");
	error = (int)(delta.x - delta.y);
	cur = start;
	printf("before while\n");
	while (1)
	{
		printf("in while\n");
		if (cur.x >= 0 && cur.x < data->window->mini_width && cur.y >= 0 && cur.y < data->window->mini_height)
			mlx_put_pixel(img, (int)cur.x, (int)cur.y, color);
		if ((int)cur.x >= (int)end.x || (int)cur.y >= (int)end.y)
			break ;
		error2 = error * 2;
		if (error2 > -(int)delta.y)
		{
			error -= (int)delta.y;
			cur.x += sign.x;
		}
		if (error2 < (int)delta.x)
		{
			error += (int)delta.x;
			cur.y += sign.y;
		}
	}
}
// void	draw_mini_line(t_data *data, double x_coord, double y_coord)
// {
// 	int dx;
// 	int dy;
// 	int sx;
// 	int sy;
// 	int err;
// 	int e2;

// 	dx = ft_abs((int)x_coord - data->player.pos.x);
// 	dy = ft_abs((int)y_coord - data->player.pos.y);
// 	if (data->player.pos.x < (int)x_coord)
// 		sx = 1;
// 	else
// 		sx = -1;
// 	if (data->player.pos.y < (int)y_coord)
// 		sy = -1;
// 	else
// 		sy = 1;
// 	err = dx - dy;
// 	while (1)
// 	{
// 		if (data->player.pos.x >= 0 && data->player.pos.x < data->window->mini_width
// 			&& data->player.pos.y >= 0 && data->player.pos.y < data->window->mini_height)
// 			mlx_put_pixel(data->window->mini_image, data->player.pos.x,
// 				data->player.pos.y, 0x00FF00FF);
// 		if (data->player.pos.x == (int)x_coord
// 			&& data->player.pos.y == (int)y_coord)
// 			break;
// 		e2 = err * 2;
// 		if (e2 > -dy)
// 		{
// 			err -= dy;
// 			data->player.pos.x += sx;
// 		}
// 		if (e2 < dx)
// 		{
// 			err += dx;
// 			data->player.pos.y -= sy;
// 		}
// 	}
// }

static void clamp_to_mini_image(t_vector_2d *point)
{
	t_data *data = static_data();
	if (point->x < 0)
		point->x = 0;
	if (point->x >= (double)data->window->mini_width)
		point->x = (double)data->window->mini_width - 1;
	if (point->y < 0)
		point->y = 0;
	if (point->y >= (double)data->window->mini_height)
		point->y = (double)data->window->mini_height - 1;
}

static void	do_mini_work(t_vector_2d start, t_vector_2d end, t_vector_2d *sign)
{
	if (start.x < end.x)
		if (start.y < end.y)
			*sign = ft_vector_init(1, 1);
		else
			*sign = ft_vector_init(1, -1);
	else if (start.y < end.y)
		*sign = ft_vector_init(-1, 1);
	else
		*sign = ft_vector_init(-1, -1);
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

// typedef struct s_line
// {
// 	double			dx;
// 	double			dy;
// 	double			sx;
// 	double			sy;
// 	double			err;
// 	double			e2;
// 	uint32_t		x;
// 	uint32_t		y;
// }					t_line;

// static void	draw_line(t_vector_2d *start, t_vector_2d *end, mlx_image_t *img, uint32_t color)
// {
// 	t_line		*line;

// 	line = init_line(start, end);
// 	while (!((line->sx > 0 && line->x > (uint32_t)end->x)
// 			|| (line->sx <= 0 && line->x < (uint32_t)end->x)
// 			|| (line->sy > 0 && line->y > (uint32_t)end->y)
// 			|| (line->sy <= 0 && line->y < (uint32_t)end->y)))
// 	{
// 		if (line->x <= img->height && line->y <= img->width)
// 			mlx_put_pixel(img, line->y, line->x, color);
// 		line->e2 = line->err;
// 		if (line->e2 > -line->dx)
// 		{
// 			line->err -= line->dy;
// 			line->x += line->sx;
// 		}
// 		if (line->e2 < line->dy)
// 		{
// 			line->err += line->dx;
// 			line->y += line->sy;
// 		}
// 	}
// 	free(line);
// }

// static t_line	*init_line(t_vector_2d *start, t_vector_2d *end)
// {
// 	t_line	*line;

// 	line = ft_calloc(1, sizeof(t_line));
// 	if (!line)
// 		return (NULL);
// 	line->dx = fabs(end->x - start->x);
// 	line->dy = fabs(end->y - start->y);
// 	if (start->x < end->x)
// 		line->sx = 1;
// 	else
// 		line->sx = -1;
// 	if (start->y < end->y)
// 		line->sy = 1;
// 	else
// 		line->sy = -1;
// 	if (line->dx > line->dy)
// 		line->err = line->dx / 2;
// 	else
// 		line->err = -(line->dy / 2);
// 	line->x = start->x;
// 	line->y = start->y;
// 	return (line);
// }
