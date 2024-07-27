/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:20:06 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/27 17:39:27 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	adjust_values(t_draw_line_data *line_data, t_vector_2d *start);

void	do_work(t_vector_2d start, t_vector_2d end, t_vector_2d *sign)
{
	if (start.x < end.x)
	{
		if (start.y < end.y)
			*sign = ft_vector_init(1, 1);
		else
			*sign = ft_vector_init(1, -1);
	}
	else if (start.y < end.y)
		*sign = ft_vector_init(-1, 1);
	else
		*sign = ft_vector_init(-1, -1);
}

void	clamp_to_window(t_vector_2d *point)
{
	t_data	*data;

	data = static_data();
	if (point->x < 0)
		point->x = 0;
	if (point->x >= data->window->width)
		point->x = data->window->width - 1;
	if (point->y < 0)
		point->y = 0;
	if (point->y >= data->window->height)
		point->y = data->window->height - 1;
}

void	draw_line(mlx_image_t *img, t_vector_2d start, t_vector_2d end,
		uint32_t color)
{
	t_draw_line_data	line_data;
	t_data				*data;

	data = static_data();
	clamp_to_window(&start);
	clamp_to_window(&end);
	line_data.delta = ft_vector_init(fabs(end.x - start.x),
			fabs(end.y - start.y));
	do_work(start, end, &(line_data.sign));
	line_data.error = (int)(line_data.delta.x - line_data.delta.y);
	while (1)
	{
		if (start.x >= 0 && start.x < data->window->width && start.y >= 0
			&& start.y < data->window->height)
			mlx_put_pixel(img, (int)start.x, (int)start.y, color);
		if ((int)start.x == (int)end.x && (int)start.y == (int)end.y)
			break ;
		adjust_values(&line_data, &start);
	}
}

static void	adjust_values(t_draw_line_data *line_data, t_vector_2d *start)
{
	line_data->error2 = line_data->error * 2;
	if (line_data->error2 > -(int)line_data->delta.y)
	{
		line_data->error -= (int)line_data->delta.y;
		start->x += line_data->sign.x;
	}
	if (line_data->error2 < (int)line_data->delta.x)
	{
		line_data->error += (int)line_data->delta.x;
		start->y += line_data->sign.y;
	}
}
