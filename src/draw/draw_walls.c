/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:41:42 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/26 15:44:39 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_some_dwd_values(t_draw_walls_data *dwd,
				const t_data *data, const t_raycast_data *rd);

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
		wrd->draw_end = data->window->height ;
}

inline void	draw_walls(const t_data *data, const t_raycast_data *rd,
	const int x)
{
	t_draw_walls_data		dwd;

	init_some_dwd_values(&dwd, data, rd);
	while (++dwd.y < dwd.wrd.draw_end)
	{
		dwd.wrd.tex_y = (int)dwd.tex_pos & (TEX_HEIGHT - 1);
		dwd.tex_pos += dwd.step;
		dwd.distance_effect = fmin(1.0, rd->perp_wall_dist / dwd.max_distance);
		dwd.blend_factor = fmax(0.0, dwd.distance_effect);
		if (dwd.wrd.tex_num == WALL)
			dwd.color = blend_color(get_pixel(data->texture[
						determine_direction(rd->ray_dir, rd->side)],
						dwd.wrd.tex_x, dwd.wrd.tex_y), dwd.blend_factor);
		else if (dwd.wrd.tex_num == PILLAR)
			dwd.color = blend_color(get_pixel(data->texture[PILLAR],
						dwd.wrd.tex_x, dwd.wrd.tex_y), dwd.blend_factor);
		else if (dwd.wrd.tex_num == DOOR_CLOSED)
			dwd.color = blend_color(get_pixel(data->texture[DOOR_CLOSED],
						dwd.wrd.tex_x, dwd.wrd.tex_y), dwd.blend_factor);
		else
			printf("Error: unknown texture\n");
		mlx_put_pixel(data->window->image, x, dwd.y, dwd.color);
	}
}

static void	init_some_dwd_values(t_draw_walls_data *dwd,
	const t_data *data, const t_raycast_data *rd)
{
	dwd->wrd.tex_num = data->map->map[rd->map.x][rd->map.y];
	calculate_wall_intersection_point(data, rd, &dwd->wrd);
	adjust_texture_x_coordinate(rd, &dwd->wrd);
	calculate_wall_projection_bounds(data, rd, &dwd->wrd);
	dwd->step = 1.0 * TEX_HEIGHT / rd->line_height;
	dwd->tex_pos = (dwd->wrd.draw_start - data->window->height / 2
			+ rd->line_height / 2) * dwd->step;
	dwd->y = dwd->wrd.draw_start - 1;
	dwd->max_distance = MAX_DARK;
}
