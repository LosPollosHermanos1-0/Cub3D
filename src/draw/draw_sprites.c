/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:10:02 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/25 17:51:16 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_vars(t_data *data, t_sprite_data *sprite,
				double *height_adj_factor, int *height_adj);

void	calculate_sprite_screen_position_and_size(t_data *data,
			t_sprite_data *sprite)
{
	double		scale_factor;

	scale_factor = 0.5;
	if (sprite->render_data.transform.y == 0)
	{
		sprite->render_data.sprite_screen_x = 0;
		sprite->render_data.sprite_height = 0;
		sprite->render_data.sprite_width = 0;
	}
	else
	{
		sprite->render_data.sprite_screen_x = (int)((data->window->width / 2)
				* (1 + sprite->render_data.transform.x
					/ sprite->render_data.transform.y));
		sprite->render_data.sprite_height = abs((int)(data->window->height
					/ sprite->render_data.transform.y)) * scale_factor;
		sprite->render_data.sprite_width = abs((int)(data->window->height
					/ sprite->render_data.transform.y)) * scale_factor;
	}
}

void	calculate_drawing_start_and_end(t_data *data, t_sprite_data *sprite)
{
	double	height_adj_factor;
	int		height_adj;

	height_adj_factor = 0.25;
	height_adj = sprite->render_data.sprite_height
		* height_adj_factor;
	sprite->render_data.draw_start_y = -sprite->render_data.sprite_height / 2
		+ data->window->height / 2 - height_adj;
	if (sprite->render_data.draw_start_y < 0)
		sprite->render_data.draw_start_y = 0;
	sprite->render_data.draw_end_y = sprite->render_data.sprite_height / 2
		+ data->window->height / 2 - height_adj;
	if (sprite->render_data.draw_end_y >= data->window->height)
		sprite->render_data.draw_end_y = data->window->height - 1;
	sprite->render_data.draw_start_x = -sprite->render_data.sprite_width / 2
		+ sprite->render_data.sprite_screen_x;
	if (sprite->render_data.draw_start_x < 0)
		sprite->render_data.draw_start_x = 0;
	sprite->render_data.draw_end_x = sprite->render_data.sprite_width / 2
		+ sprite->render_data.sprite_screen_x;
	if (sprite->render_data.draw_end_x >= data->window->width)
		sprite->render_data.draw_end_x = data->window->width - 1;
}

void	draw_sprite(t_data *data, t_sprite_data *sprite)
{
	double		height_adj_factor;
	int			height_adj;
	int			stripe;
	int			y;
	uint32_t	color;

	fill_vars(data, sprite, &height_adj_factor, &height_adj);
	stripe = sprite->render_data.draw_start_x - 1;
	while (++stripe < sprite->render_data.draw_end_x)
	{
		sprite->render_data.tex_x = (stripe - (-sprite->render_data.sprite_width
					/ 2 + sprite->render_data.sprite_screen_x))
			* TEX_WIDTH_FLOOR / sprite->render_data.sprite_width;
		if (sprite->render_data.transform.y > 0 && stripe > 0 && stripe
			< data->window->width && sprite->render_data.transform.y
			< data->z_buffer[stripe])
		{
			y = sprite->render_data.draw_start_y - 1;
			while (++y < sprite->render_data.draw_end_y)
			{
				sprite->render_data.d = (y + height_adj) * 256
					- data->window->height * 128
					+ sprite->render_data.sprite_height * 128;
				sprite->render_data.tex_y = ((sprite->render_data.d
							* TEX_HEIGHT_FLOOR)
						/ sprite->render_data.sprite_height) / 256;
				color = get_pixel(data->sprite_t[sprite->texture],
						sprite->render_data.tex_x, sprite->render_data.tex_y);
				if ((color & 0x00FFFFFF) != 0)
					mlx_put_pixel(data->window->image, stripe, y, color);
			}
		}
	}
}

static void	fill_vars(t_data *data, t_sprite_data *sprite,
	double *height_adj_factor, int *height_adj)
{
	double	inv_det;

	if (mlx_get_time() > sprite->last_animation_change
		+ sprite->animation_speed)
	{
		sprite->texture = (sprite->texture + 1) % 2;
		sprite->last_animation_change = mlx_get_time();
	}
	sprite->render_data.rela_pos.x = sprite->pos.x - data->player.pos.x;
	sprite->render_data.rela_pos.y = sprite->pos.y - data->player.pos.y;
	inv_det = 1.0 / (data->player.plane.x * data->player.dir.y
			- data->player.dir.x * data->player.plane.y);
	sprite->render_data.transform.x = inv_det * (data->player.dir.y
			* sprite->render_data.rela_pos.x - data->player.dir.x
			* sprite->render_data.rela_pos.y);
	sprite->render_data.transform.y = inv_det * (-data->player.plane.y
			* sprite->render_data.rela_pos.x + data->player.plane.x
			* sprite->render_data.rela_pos.y);
	calculate_sprite_screen_position_and_size(data, sprite);
	calculate_drawing_start_and_end(data, sprite);
	(*height_adj_factor) = 0.25;
	(*height_adj) = sprite->render_data.sprite_height
		* (*height_adj_factor);
}
