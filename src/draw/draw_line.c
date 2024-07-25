/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:20:06 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/25 16:22:11 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	t_data		*data;
	t_vector_2d	delta;
	t_vector_2d	sign;
	t_vector_2d	cur;
	int			error;
	int			error2;

	data = static_data();
	clamp_to_window(&start);
	clamp_to_window(&end);
	delta = ft_vector_init(fabs(end.x - start.x), fabs(end.y - start.y));
	do_work(start, end, &sign);
	error = (int)(delta.x - delta.y);
	cur = start;
	while (1)
	{
		if (cur.x >= 0 && cur.x < data->window->width && cur.y >= 0
			&& cur.y < data->window->height)
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
