/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_and_ceiling.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 22:05:52 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/26 15:44:39 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_pixels(t_draw_floor_and_ceiling_data *fcd, t_data *data, int y);

uint32_t	blend_color(uint32_t originalColor, float blend_factor)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	r = (originalColor >> 24) & 0xFF;
	g = (originalColor >> 16) & 0xFF;
	b = (originalColor >> 8) & 0xFF;
	r *= (1 - blend_factor);
	g *= (1 - blend_factor);
	b *= (1 - blend_factor);
	return (((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8)
		| 0xFF);
}

uint32_t	blend_two_colors(uint32_t color1, uint32_t color2,
	float blend_factor)
{
	uint8_t		rgb1[3];
	uint8_t		rgb2[3];
	uint8_t		r_result;
	uint8_t		g_result;
	uint8_t		b_result;

	rgb1[0] = (color1 >> 24) & 0xFF;
	rgb1[1] = (color1 >> 16) & 0xFF;
	rgb1[2] = (color1 >> 8) & 0xFF;
	rgb2[0] = (color2 >> 24) & 0xFF;
	rgb2[1] = (color2 >> 16) & 0xFF;
	rgb2[2] = (color2 >> 8) & 0xFF;
	r_result = (uint8_t)(rgb1[0] + (rgb2[0] - rgb1[0]) * blend_factor);
	g_result = (uint8_t)(rgb1[1] + (rgb2[1] - rgb1[1]) * blend_factor);
	b_result = (uint8_t)(rgb1[2] + (rgb2[2] - rgb1[2]) * blend_factor);
	return (((uint32_t)r_result << 24) | ((uint32_t)g_result << 16)
		| ((uint32_t)b_result << 8) | 0xFF);
}

bool	is_in_circle(t_vector_2d center, double radius, t_vector_2d point)
{
	return ((point.x - center.x) * (point.x - center.x)
		+ (point.y - center.y) * (point.y - center.y) <= radius * radius);
}

inline void	draw_floor_and_ceiling(t_data *data, int y)
{
	t_draw_floor_and_ceiling_data	fcd;

	fcd.half_height = data->window->height / 2.0;
	fcd.position = y - fcd.half_height;
	fcd.row_distance = fcd.half_height / fcd.position;
	fcd.ray_dir_left = ft_vector_sub(data->player.dir, data->player.plane);
	fcd.ray_dir_right = ft_vector_add(data->player.dir, data->player.plane);
	fcd.floor_step = ft_vector_div(ft_vector_scale(ft_vector_sub(
					fcd.ray_dir_right, fcd.ray_dir_left), fcd.row_distance),
			(t_vector_2d){data->window->width, data->window->width});
	fcd.floor = ft_vector_add(data->player.pos,
			ft_vector_scale(fcd.ray_dir_left, fcd.row_distance));
	fcd.x = -1;
	while (++fcd.x < data->window->width)
	{
		fcd.cell = (t_coordinate){(int)fcd.floor.x, (int)fcd.floor.y};
		fcd.texture = (t_coordinate){(int)(TEX_WIDTH_FLOOR
				* (fcd.floor.x - fcd.cell.x)) & (TEX_WIDTH_FLOOR - 1),
			(int)(TEX_HEIGHT_FLOOR * (fcd.floor.y - fcd.cell.y))
			& (TEX_HEIGHT_FLOOR - 1)};
		fcd.blend_factor = fminf(1.0, fmaxf(0.0, 1.0 - fcd.position
					/ fcd.half_height));
		put_pixels(&fcd, data, y);
		fcd.floor = ft_vector_add(fcd.floor, fcd.floor_step);
	}
}

static void	put_pixels(t_draw_floor_and_ceiling_data *fcd, t_data *data, int y)
{
	mlx_put_pixel(data->window->image, fcd->x, y,
		blend_color(get_pixel(data->texture[FLOOR], fcd->texture.x,
				fcd->texture.y), fcd->blend_factor));
	mlx_put_pixel(data->window->image, fcd->x, data->window->height - y - 1,
		blend_color(get_pixel(data->texture[CEILING], fcd->texture.x,
				fcd->texture.y), fcd->blend_factor));
}
