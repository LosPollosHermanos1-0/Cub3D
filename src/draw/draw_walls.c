/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:41:42 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/03 02:42:09 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calculate_wall_intersection_point(const t_data *data,
		const t_raycast_data *rd, t_wall_rendering_data *wrd)
{
	if (rd->side == 0)
		wrd->wall_x = data->player.pos.y + rd->perp_wall_dist * rd->ray_dir.y;
	else
		wrd->wall_x = data->player.pos.x + rd->perp_wall_dist * rd->ray_dir.x;
	wrd->wall_x -= floor(wrd->wall_x);
}

static void	adjust_texture_x_coordinate(const t_raycast_data *rd,
		t_wall_rendering_data *wrd)
{
	wrd->tex_x = (int)(wrd->wall_x * (double)TEX_WIDTH);
	if ((rd->side == 0 && rd->ray_dir.x > 0) || (rd->side == 1
			&& rd->ray_dir.y < 0))
	{
		wrd->tex_x = TEX_WIDTH - wrd->tex_x - 1;
	}
}

static void	calculate_wall_projection_bounds(const t_data *data,
		const t_raycast_data *rd, t_wall_rendering_data *wrd)
{
	wrd->draw_start = -rd->line_height / 2 + data->window->height / 2;
	if (wrd->draw_start < 0)
		wrd->draw_start = 0;
	wrd->draw_end = rd->line_height / 2 + data->window->height / 2;
	if (wrd->draw_end >= data->window->height)
		wrd->draw_end = data->window->height - 1;
}

inline void	draw_walls(const t_data *data, const t_raycast_data *rd, const int x)
{
	u_int32_t				color;
	t_wall_rendering_data	wrd;
	double					step;
	double					tex_pos;
	int						y;

	wrd.tex_num = data->map->map[rd->map.x][rd->map.y] - 1;
	calculate_wall_intersection_point(data, rd, &wrd);
	adjust_texture_x_coordinate(rd, &wrd);
	calculate_wall_projection_bounds(data, rd, &wrd);
	step = 1.0 * TEX_HEIGHT / rd->line_height;
	tex_pos = (wrd.draw_start - data->window->height / 2 + rd->line_height / 2)
		* step;
	y = wrd.draw_start;
	while (y < wrd.draw_end)
	{
		wrd.tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		color = get_pixel(data->texture[wrd.tex_num], wrd.tex_x, wrd.tex_y);
		if (rd->side == 1)
			color = (color >> 1) & 8355711;//TODO remove
		mlx_put_pixel(data->window->image, x, y, color);
		y++;
	}
}
