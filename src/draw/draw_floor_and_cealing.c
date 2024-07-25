/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_and_cealing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 22:05:52 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/25 14:09:32 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	blend_color(uint32_t originalColor, float blendFactor)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	r = (originalColor >> 24) & 0xFF;
	g = (originalColor >> 16) & 0xFF;
	b = (originalColor >> 8) & 0xFF;
	r *= (1 - blendFactor);
	g *= (1 - blendFactor);
	b *= (1 - blendFactor);
	return (((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8)
		| 0xFF);
}

uint32_t	blend_two_colors(uint32_t color1, uint32_t color2,
	float blendFactor)
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
	r_result = (uint8_t)(rgb1[0] + (rgb2[0] - rgb1[0]) * blendFactor);
	g_result = (uint8_t)(rgb1[1] + (rgb2[1] - rgb1[1]) * blendFactor);
	b_result = (uint8_t)(rgb1[2] + (rgb2[2] - rgb1[2]) * blendFactor);
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
	double			half_height;
	double			position;
	double			row_distance;

	half_height = data->window->height / 2.0;
	position = y - half_height;
	row_distance = half_height / position;

	t_vector_2d		ray_dir_left;
	t_vector_2d		ray_dir_right;
	t_vector_2d		floor_step;
	t_vector_2d		floor;
	ray_dir_left = ft_vector_sub(data->player.dir, data->player.plane);
	ray_dir_right = ft_vector_add(data->player.dir, data->player.plane);
	floor_step = ft_vector_div(ft_vector_scale(ft_vector_sub(ray_dir_right, ray_dir_left), row_distance), (t_vector_2d){data->window->width, data->window->width});
	floor = ft_vector_add(data->player.pos, ft_vector_scale(ray_dir_left, row_distance));

	// t_coordinate		cell[2];
	// t_coordinate		texture[2];
	float				blendFactor;
	int				x;
	x = -1;
	while (++x < data->window->width)
	{
		t_coordinate	cell = {(int)floor.x, (int)floor.y};
		t_coordinate	texture = {(int)(TEX_WIDTH_FLOOR * (floor.x - cell.x)) & (TEX_WIDTH_FLOOR - 1),
		(int)(TEX_HEIGHT_FLOOR * (floor.y - cell.y)) & (TEX_HEIGHT_FLOOR - 1)
		};

		blendFactor = fminf(1.0, fmaxf(0.0, 1.0 - position / half_height));

		// uint32_t floorColor = blend_color(get_pixel(data->texture[FLOOR], texture.x, texture.y), blendFactor);
		// uint32_t ceilingColor = blend_color(get_pixel(data->texture[CEILING], texture.x, texture.y), blendFactor);

		mlx_put_pixel(data->window->image, x, y, blend_color(get_pixel(data->texture[FLOOR], texture.x, texture.y), blendFactor));
		mlx_put_pixel(data->window->image, x, data->window->height - y - 1, blend_color(get_pixel(data->texture[CEILING], texture.x, texture.y), blendFactor));

		floor = ft_vector_add(floor, floor_step);
	}
}
