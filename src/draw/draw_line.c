/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:20:06 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/01 10:58:15 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	do_work(t_vector_2d start, t_vector_2d end, t_vector_2d *sign)
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

void clamp_to_window(t_vector_2d *point) {
	t_data *data = static_data();
	if (point->x < 0) point->x = 0;
	if (point->x >= data->window->width) point->x = data->window->width - 1;
	if (point->y < 0) point->y = 0;
	if (point->y >= data->window->height) point->y = data->window->height - 1;
}

void	draw_line(mlx_image_t *img, t_vector_2d start, t_vector_2d end,
		uint32_t color)
{
	t_data		*data = static_data();
	t_vector_2d	delta;
	t_vector_2d	sign;
	t_vector_2d	cur;
	int			error;
	int			error2;

	clamp_to_window(&start);
	clamp_to_window(&end);

	delta = ft_vector_init(fabs(end.x - start.x), fabs(end.y - start.y));
	do_work(start, end, &sign);
	error = (int)(delta.x - delta.y);
	cur = start;
	while (1)
	{
		if (cur.x >= 0 && cur.x < data->window->width && cur.y >= 0 && cur.y < data->window->height)
			mlx_put_pixel(img, (int)cur.x, (int)cur.y, color);
		if ((int)cur.x == (int)end.x && (int)cur.y == (int)end.y)
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


void draw_line_vector(mlx_image_t *img, t_vector_2d start, t_vector_2d direction, uint32_t color) {
	int x0 = (int)round(start.x);
	int y0 = (int)round(start.y);
	int x1 = (int)round(start.x + direction.x);
	int y1 = (int)round(start.y + direction.y);

	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);

	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;

	int err = dx - dy;
	int e2;

	while (1) {
		mlx_put_pixel(img, x0, y0, color);

		if (x0 == x1 && y0 == y1) {
			break;
		}

		e2 = 2 * err;

		if (e2 > -dy) {
			err -= dy;
			x0 += sx;
		}

		if (e2 < dx) {
			err += dx;
			y0 += sy;
		}
	}
}