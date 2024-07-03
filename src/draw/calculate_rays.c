/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_rays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:52:02 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/02 23:52:34 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_step_and_side_distance(const t_data *data, t_raycast_data *rd)
{
	if (rd->ray_dir.x < 0)
	{
		rd->step_x = -1;
		rd->side_dist.x = (data->player->pos.x - rd->map_x) * rd->delta_dist.x;
	}
	else
	{
		rd->step_x = 1;
		rd->side_dist.x = (rd->map_x + 1.0 - data->player->pos.x)
			* rd->delta_dist.x;
	}
	if (rd->ray_dir.y < 0)
	{
		rd->step_y = -1;
		rd->side_dist.y = (data->player->pos.y - rd->map_y) * rd->delta_dist.y;
	}
	else
	{
		rd->step_y = 1;
		rd->side_dist.y = (rd->map_y + 1.0 - data->player->pos.y)
			* rd->delta_dist.y;
	}
}

void	processe_ray_collision(const t_data *data, t_raycast_data *rd)
{
	while (rd->hit == 0)
	{
		if (rd->side_dist.x < rd->side_dist.y)
		{
			rd->side_dist.x += rd->delta_dist.x;
			rd->map_x += rd->step_x;
			rd->side = 0;
		}
		else
		{
			rd->side_dist.y += rd->delta_dist.y;
			rd->map_y += rd->step_y;
			rd->side = 1;
		}
		if (data->map->map[rd->map_x][rd->map_y] > 0)
		{
			rd->hit = 1;
		}
	}
}

void	calculate_perpendicular_wall_distance(t_raycast_data *rd)
{
	if (rd->side == 0)
		rd->perp_wall_dist = rd->side_dist.x - rd->delta_dist.x;
	else
		rd->perp_wall_dist = rd->side_dist.y - rd->delta_dist.y;
}

void	draw_rays(void)
{
	t_data			*data;
	t_raycast_data	*rd;

	data = static_data();
	for (int x = 0; x < WINDOW_W; ++x)
	{
		rd = init_raycast_data(data, x);
		calculate_step_and_side_distance(data, rd);
		processe_ray_collision(data, rd);
		calculate_perpendicular_wall_distance(rd);
		rd->line_height = (int)(WINDOW_H / rd->perp_wall_dist);
		draw_walls(data, rd, x);
		free(rd);
	}
}
