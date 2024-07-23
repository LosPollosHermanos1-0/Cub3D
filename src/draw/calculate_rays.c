/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_rays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:52:02 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/18 15:07:02 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calculate_step_and_side_distance(const t_data *data,
				t_raycast_data *rd)
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

static void set_door_flags(t_data *data, bool isCenterRay, bool hitClosedDoor, bool hitOpenDoor) {
	if (isCenterRay) {
		if (hitOpenDoor)
			data->flags |= FLAG_FACING_OPEN_DOOR;
		else
			data->flags &= ~FLAG_FACING_OPEN_DOOR;
		if (hitClosedDoor && !hitOpenDoor)
			data->flags |= FLAG_FACING_CLOSED_DOOR;
		else
			data->flags &= ~FLAG_FACING_CLOSED_DOOR;
	}
}


double calculate_distance(t_vector_2d point1, t_vector_2d point2) {
	return sqrt((point2.x - point1.x) * (point2.x - point1.x) + (point2.y - point1.y) * (point2.y - point1.y));
}

static void handle_collision(t_data *data, t_raycast_data *rd, bool *hitClosedDoor, bool *hitOpenDoor) {
	char cell = data->map->map[rd->map.x][rd->map.y];
	double distance = calculate_distance(data->player.pos, (t_vector_2d){rd->map.x + 0.5, rd->map.y + 0.5});
	if (cell == WALL || cell == PILLAR) {
		rd->hit = 1;
	} else if (cell == DOOR_CLOSED) {
		if(distance <= DOOR_INTERACTION_DIST && !*hitClosedDoor) {
			data->last_faced_closed_door = (t_vector_2d){rd->map.x, rd->map.y};
			*hitClosedDoor = true;
		}
		rd->hit = 1;
	} else if (cell == DOOR_OPEN && distance <= DOOR_INTERACTION_DIST) {
		if(!*hitOpenDoor)
			data->last_faced_open_door = (t_vector_2d){rd->map.x, rd->map.y};
		*hitOpenDoor = true;
	}
}

static void processe_ray_collision(t_data *data, t_raycast_data *rd, int ray_index) {
	bool isCenterRay = (ray_index == data->window->width / 2);
	bool hitClosedDoor = false;
	bool hitOpenDoor = false;

	while (rd->hit == 0) {
		if (rd->side_dist.x < rd->side_dist.y) {
			rd->side_dist.x += rd->delta_dist.x;
			rd->map.x += rd->step.x;
			rd->side = 0;
		} else {
			rd->side_dist.y += rd->delta_dist.y;
			rd->map.y += rd->step.y;
			rd->side = 1;
		}
		handle_collision(data, rd, &hitClosedDoor, &hitOpenDoor);
	}
	set_door_flags(data, isCenterRay, hitClosedDoor, hitOpenDoor);
}

static void	calculate_perpendicular_wall_distance(const t_data *data,
				t_raycast_data *rd, int x)
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
	int				y;
	int				x;

	data = static_data();
	y = data->window->height / 2 + 1;
	while (y < data->window->height)
	{
		draw_floor_and_ceiling(data, y);
		y++;
	}
	x = 0;
	while (x < data->window->width)
	{
		rd = init_raycast_data(data, x);
		calculate_step_and_side_distance(data, &rd);
		processe_ray_collision(data, &rd, x);
		calculate_perpendicular_wall_distance(data, &rd, x);
		rd.line_height = (int)(data->window->height / rd.perp_wall_dist);
		draw_walls(data, &rd, x);
		x++;
	}
}
