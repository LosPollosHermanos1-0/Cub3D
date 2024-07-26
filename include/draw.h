/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:21:49 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/26 15:33:16 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# define TEX_WIDTH 128
# define TEX_HEIGHT 128

# define TEX_WIDTH_FLOOR 64
# define TEX_HEIGHT_FLOOR 64

# define MAX_DARK 10.0

# include "cub3d.h"

typedef struct s_coordinate
{
	int						x;
	int						y;
}							t_coordinate;

typedef struct s_raycast_data
{
	double					camera_x;
	t_vector_2d				ray_dir;
	t_vector_2d				delta_dist;
	t_coordinate			map;
	t_vector_2d				side_dist;
	double					perp_wall_dist;
	t_coordinate			step;
	int						hit;
	int						side;
	int						line_height;
}							t_raycast_data;

typedef struct s_wall_rendering_data
{
	int						tex_num;
	int						tex_x;
	int						tex_y;
	double					wall_x;
	double					draw_start;
	double					draw_end;
	double					step;
	double					tex_pos;
}							t_wall_rendering_data;

typedef struct s_sprite_rendering_data
{
	t_vector_2d				transform;
	t_vector_2d				rela_pos;
	double					distance;
	long long				sprite_screen_x;
	long long				sprite_height;
	long long				draw_start_y;
	long long				draw_end_y;
	long long				sprite_width;
	long long				draw_start_x;
	long long				draw_end_x;
	long long				tex_x;
	long long				tex_y;
	long long				color;
	long long				d;
}							t_sprite_rendering_data;

typedef struct s_sprite_data
{
	t_vector_2d				pos;
	t_vector_2d				dir;
	t_sprite_rendering_data	render_data;
	double					last_animation_change;
	double					animation_speed;
	double					last_idle;
	double					last_move;
	int						texture;
	double					move_speed;
	double					distance_to_player;
	t_opponent_state		state;
}							t_sprite_data;

typedef struct s_draw_line_data
{
	t_vector_2d				delta;
	t_vector_2d				sign;
	int						error;
	int						error2;
}							t_draw_line_data;

typedef struct s_draw_walls_data {
	uint32_t				color;
	t_wall_rendering_data	wrd;
	double					step;
	double					tex_pos;
	int						y;
	double					maxDistance;
	double					distanceEffect;
	double					blendFactor;
}							t_draw_walls_data;

typedef struct s_draw_floor_and_ceiling_data {
	double					half_height;
	double					position;
	double					row_distance;
	t_vector_2d				ray_dir_left;
	t_vector_2d				ray_dir_right;
	t_vector_2d				floor_step;
	t_vector_2d				floor;
	float					blendFactor;
	int						x;
	t_coordinate			cell;
	t_coordinate			texture;
}							t_draw_floor_and_ceiling_data;


// void		draw_line_vector(mlx_image_t *img,
// 				t_vector_2d start, t_vector_2d direction,
// 				uint32_t color);
void		draw_rays(void);
uint32_t	get_pixel(const mlx_texture_t *texture, uint32_t x,
				uint32_t y);
void		draw_walls(const t_data *data,
				const t_raycast_data *rd, const int x);
void		draw_floor_and_ceiling(t_data *data, int y);
void		draw_sprite(t_data *data, t_sprite_data *sprite);
void		draw_mini_map(t_data *data);
uint32_t	blend_color(uint32_t originalColor, float blendFactor);
bool		is_in_circle(t_vector_2d center, double radius, t_vector_2d point);
void		draw_door_icon(t_data *data);
void		move_opponent(t_data *data, t_sprite_data *opponent);
void		sort_sprites(t_data *data);
bool		ft_is_point_in_triangle(t_vector_2d *point, t_vector_2d *a,
				t_vector_2d *b, t_vector_2d *c);
bool		ft_is_point_in_circle(t_vector_2d center, double radius,
				t_vector_2d point);

#endif // DRAW_H
