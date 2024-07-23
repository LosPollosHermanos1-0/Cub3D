/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_rays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:52:02 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/03 02:56:49 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calculate_step_and_side_distance(const t_data *data, t_raycast_data *rd)
{
	if (rd->ray_dir.x < 0)
	{
		rd->step.x = -1;
		rd->side_dist.x = (data->player.pos.x - rd->map.x) * rd->delta_dist.x;
	}
	else
	{
		rd->step.x = 1;
		rd->side_dist.x = (rd->map.x + 1.0 - data->player.pos.x)
			* rd->delta_dist.x;
	}
	if (rd->ray_dir.y < 0)
	{
		rd->step.y = -1;
		rd->side_dist.y = (data->player.pos.y - rd->map.y) * rd->delta_dist.y;
	}
	else
	{
		rd->step.y = 1;
		rd->side_dist.y = (rd->map.y + 1.0 - data->player.pos.y)
			* rd->delta_dist.y;
	}
}

static void	processe_ray_collision(t_data *data, t_raycast_data *rd, int rayIndex)
{
	bool isCenterRay = (rayIndex == data->window->width / 2);
	bool has_hit_closed_door = false;
	bool has_hit_open_door = false;
	while (rd->hit == 0)
	{
		if (rd->side_dist.x < rd->side_dist.y)
		{
			rd->side_dist.x += rd->delta_dist.x;
			rd->map.x += rd->step.x;
			rd->side = 0;
		}
		else
		{
			rd->side_dist.y += rd->delta_dist.y;
			rd->map.y += rd->step.y;
			rd->side = 1;
		}

		if (data->map->map[rd->map.x][rd->map.y] == WALL || data->map->map[rd->map.x][rd->map.y] == PILLAR || data->map->map[rd->map.x][rd->map.y] == DOOR)
		{
			if (isCenterRay && data->map->map[rd->map.x][rd->map.y] == DOOR) {
				data->last_faced_closed_door = (t_vector_2d){rd->map.x, rd->map.y};
				data->flags |= FLAG_FACING_CLOSED_DOOR;
				has_hit_closed_door = true;
			}
			rd->hit = 1;
		}

		if (isCenterRay && data->map->map[rd->map.x][rd->map.y] == DOOR_OPEN && !(data->flags & FLAG_FACING_OPEN_DOOR)) {
			data->last_faced_open_door = (t_vector_2d){rd->map.x, rd->map.y};
			data->flags |= FLAG_FACING_OPEN_DOOR;
			has_hit_open_door = true;
		}
	}
	if (isCenterRay && !has_hit_closed_door && data->flags & FLAG_FACING_CLOSED_DOOR) {
		data->flags &= ~FLAG_FACING_CLOSED_DOOR;
	}
	if (isCenterRay && !has_hit_open_door && data->flags & FLAG_FACING_OPEN_DOOR) {
		data->flags &= ~FLAG_FACING_OPEN_DOOR;
	}
}

static void	calculate_perpendicular_wall_distance(const t_data *data, t_raycast_data *rd, int x)
{
	if (rd->side == 0)
		rd->perp_wall_dist = rd->side_dist.x - rd->delta_dist.x;
	else
		rd->perp_wall_dist = rd->side_dist.y - rd->delta_dist.y;
	data->z_buffer[x] = rd->perp_wall_dist;
}
void	draw_rays(void)
{
	t_data			*data;
	t_raycast_data	rd;

	data = static_data();
	for (int y = data->window->height / 2 + 1; y < data->window->height; y++) {
		draw_floor_and_ceiling(data, y);
	}

	for (int x = 0; x < data->window->width; ++x)
	{
		rd = init_raycast_data(data, x);
		calculate_step_and_side_distance(data, &rd);
		processe_ray_collision(data, &rd, x);
		calculate_perpendicular_wall_distance(data, &rd, x);
		rd.line_height = (int)(data->window->height / rd.perp_wall_dist);
		draw_walls(data, &rd, x);
	}
}
