/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_spites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:10:02 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/04 14:10:07 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_relative_position(t_data *data, t_sprite_data *sprite)
{
	sprite->render_data.rela_pos.x = sprite->pos.x - data->player.pos.x;
	sprite->render_data.rela_pos.y = sprite->pos.y - data->player.pos.y;
}

void	calculate_transformation(t_data *data, t_sprite_data *sprite)
{
	double	inv_det;

	inv_det = 1.0 / (data->player.plane.x * data->player.dir.y
			- data->player.dir.x * data->player.plane.y);
	sprite->render_data.transform.x = inv_det * (data->player.dir.y
			* sprite->render_data.rela_pos.x - data->player.dir.x
			* sprite->render_data.rela_pos.y);
	sprite->render_data.transform.y = inv_det * (-data->player.plane.y
			* sprite->render_data.rela_pos.x + data->player.plane.x
			* sprite->render_data.rela_pos.y);
}

void	calculate_sprite_screen_position_and_size(t_data *data,
		t_sprite_data *sprite)
{
	sprite->render_data.sprite_screen_x = (int)((data->window->width / 2) * (1
				+ sprite->render_data.transform.x
				/ sprite->render_data.transform.y));
	sprite->render_data.sprite_height = abs((int)(data->window->height
				/ (sprite->render_data.transform.y)));
	sprite->render_data.sprite_width = abs((int)(data->window->height
				/ (sprite->render_data.transform.y)));
}

void	calculate_drawing_start_and_end(t_data *data, t_sprite_data *sprite)
{
	sprite->render_data.draw_start_y = -sprite->render_data.sprite_height / 2
		+ data->window->height / 2;
	if (sprite->render_data.draw_start_y < 0)
		sprite->render_data.draw_start_y = 0;
	sprite->render_data.draw_end_y = sprite->render_data.sprite_height / 2
		+ data->window->height / 2;
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
	if (mlx_get_time() > sprite->last_animation_change + sprite->animation_speed)
	{
		sprite->texture = (sprite->texture + 1) %2;
		sprite->last_animation_change = mlx_get_time();
	}
	calculate_relative_position(data, sprite);
	calculate_transformation(data, sprite);
	calculate_sprite_screen_position_and_size(data, sprite);
	calculate_drawing_start_and_end(data, sprite);
	// Step 4: Drawing loop
	for(int stripe = sprite->render_data.draw_start_x; stripe < sprite->render_data.draw_end_x; stripe++) {
		sprite->render_data.tex_x = (int)(256 * (stripe - (-sprite->render_data.sprite_width / 2 + sprite->render_data.sprite_screen_x)) * TEX_WIDTH / sprite->render_data.sprite_width) / 256;
		if(sprite->render_data.transform.y > 0 && stripe > 0 && stripe < data->window->width && sprite->render_data.transform.y < data->z_buffer[stripe]) {
			for(int y = sprite->render_data.draw_start_y; y < sprite->render_data.draw_end_y; y++) {
				sprite->render_data.d = (y) * 256 - data->window->height * 128 + sprite->render_data.sprite_height * 128;
				sprite->render_data.tex_y = ((sprite->render_data.d * TEX_HEIGHT) / sprite->render_data.sprite_height) / 256;
				uint32_t color = get_pixel(data->sprite_t[sprite->texture], sprite->render_data.tex_x, sprite->render_data.tex_y);
				if((color & 0x00FFFFFF) != 0) mlx_put_pixel(data->window->image, stripe, y, color);
			}
		}
	}
}
