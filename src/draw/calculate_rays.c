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

// uint32_t	create_color(const uint8_t alpha, const uint8_t red,
// 		const uint8_t green, const uint8_t blue)
// {
// 	return ((red << 24) | (green << 16) | (blue << 8) | alpha);
// }
//
// void	set_color_based_on_map(const int number, uint32_t *color)
// {
// 	switch (number)
// 	{
// 	case 1:
// 		*color = create_color(0xFF, 0xFF, 0x00, 0x00); // Red
// 		break ;
// 	case 2:
// 		*color = create_color(0xFF, 0x00, 0xFF, 0x00); // Green
// 		break ;
// 	case 3:
// 		*color = create_color(0xFF, 0x00, 0x00, 0xFF); // Blue
// 		break ;
// 	case 4:
// 		*color = create_color(0xFF, 0xFF, 0xFF, 0x00); // Yellow
// 		break ;
// 	default:
// 		*color = create_color(0xFF, 0xFF, 0xFF, 0xFF); // White
// 		break ;
// 	}
// }

t_vector_2d	calculate_delta_dist(t_vector_2d ray_dir)
{
	t_vector_2d	delta_dist;

	if (ray_dir.x != 0)
		delta_dist.x = fabs(1 / ray_dir.x);
	else
		delta_dist.x = INFINITY;
	if (ray_dir.y != 0)
		delta_dist.y = fabs(1 / ray_dir.y);
	else
		delta_dist.y = INFINITY;
	return (delta_dist);
}

t_direction	determine_direction(const t_vector_2d ray_dir, const int side)
{
	t_direction	direction;

	if (side == 0)
	{
		if (ray_dir.x < 0)
			direction = WEST;
		else
			direction = EAST;
	}
	else
	{
		if (ray_dir.y < 0)
			direction = NORTH;
		else
			direction = SOUTH;
	}
	return (direction);
}

t_raycast_data	*init_raycast_data(const t_data *data, const int x)
{
	t_raycast_data	*rd;

	rd = malloc(sizeof(t_raycast_data));
	rd->camera_x = 2 * x / (double)WINDOW_W - 1;
	rd->ray_dir = (t_vector_2d){data->player->dir.x + data->player->plane.x
		* rd->camera_x, data->player->dir.y + data->player->plane.y
		* rd->camera_x};
	rd->delta_dist = calculate_delta_dist(rd->ray_dir);
	rd->map_x = (int)data->player->pos.x;
	rd->map_y = (int)data->player->pos.y;
	rd->side_dist = (t_vector_2d){0, 0};
	rd->perp_wall_dist = 0;
	rd->step_x = 0;
	rd->step_y = 0;
	rd->hit = 0;
	rd->side = 0;
	rd->line_height = 0;
	return (rd);
}

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
	if(rd->side == 0)
		rd->perp_wall_dist = rd->side_dist.x - rd->delta_dist.x;
	else
		rd->perp_wall_dist = rd->side_dist.y - rd->delta_dist.y;
}

void	draw_rays(void)
{
	t_data			*data;
	t_raycast_data	*rd;
	u_int32_t		color;
	// t_vector_2d		start;
	// t_vector_2d		end;

	data = static_data();
	for (int x = 0; x < WINDOW_W; ++x)
	{
		rd = init_raycast_data(data, x);
		calculate_step_and_side_distance(data, rd);
		processe_ray_collision(data, rd);
		calculate_perpendicular_wall_distance(rd);
		rd->line_height = (int)(WINDOW_H / rd->perp_wall_dist);

		int tex_num = data->map->map[rd->map_x][rd->map_y] - 1;

		double wall_x;
		if (rd->side == 0)
			wall_x = data->player->pos.y + rd->perp_wall_dist * rd->ray_dir.y;
		else
			wall_x = data->player->pos.x + rd->perp_wall_dist * rd->ray_dir.x;
		wall_x -= floor(wall_x);

		int tex_x = (int)(wall_x * (double)TEX_WIDTH);
		if (rd->side == 0 && rd->ray_dir.x > 0)
			tex_x = TEX_WIDTH - tex_x - 1;
		if (rd->side == 1 && rd->ray_dir.y < 0)
			tex_x = TEX_WIDTH - tex_x - 1;

		double draw_start = -rd->line_height / 2 + WINDOW_H / 2;
		if (draw_start < 0)
			draw_start = 0;
		double draw_end = rd->line_height / 2 + WINDOW_H / 2;
		if (draw_end >= WINDOW_H)
			draw_end = WINDOW_H - 1;

		double step = 1.0 * TEX_HEIGHT / rd->line_height;
		double tex_pos = (draw_start - WINDOW_H / 2 + rd->line_height / 2) * step;


		for (int y = draw_start; y < draw_end; y++)
		{
			int tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
			tex_pos += step;
			color = get_pixel(data->texture[tex_num], tex_x, tex_y);
			if(rd->side == 1) color = (color >> 1) & 8355711;
			mlx_put_pixel(data->window->image, x, y, color);
		}


		// set_color_based_on_map(data->map->map[rd->map_x][rd->map_y], &color);
		// if (rd->side == 1)
		// {
		// 	color = color / 2;
		// }
		// start = ft_vector_init(x, WINDOW_H / 2 - line_height / 2);
		// end = ft_vector_init(x, WINDOW_H / 2 + line_height / 2);
		// draw_line(data->window->image, start, end, color);
		free(rd);
	}
}
