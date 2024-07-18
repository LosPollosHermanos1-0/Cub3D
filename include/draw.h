/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:21:49 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/18 14:24:04 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# define TEX_WIDTH 128
# define TEX_HEIGHT 128

# define TEX_WIDTH_FLOOR 64
# define TEX_HEIGHT_FLOOR 64

// typedef enum e_direction
// {
// 	NORTH,
// 	EAST,
// 	SOUTH,
// 	WEST
// }					t_direction;

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
	int						sprite_screen_x;
	int						sprite_height;
	int						draw_start_y;
	int						draw_end_y;
	int						sprite_width;
	int						draw_start_x;
	int						draw_end_x;
	int						tex_x;
	int						tex_y;
	int						color;
	int						d;
}							t_sprite_rendering_data;

typedef struct s_sprite_data
{
	t_vector_2d				pos;
	t_sprite_rendering_data	render_data;
	double					last_animation_change;
	double					animation_speed;
	int						texture;
}							t_sprite_data;

void						draw_line(mlx_image_t *img, t_vector_2d start,
								t_vector_2d end, uint32_t color);
void						draw_line_vector(mlx_image_t *img,
								t_vector_2d start, t_vector_2d direction,
								uint32_t color);
void						draw_rays(void);
uint32_t					get_pixel(const mlx_texture_t *texture, uint32_t x,
								uint32_t y);
void						draw_walls(const t_data *data,
								const t_raycast_data *rd, const int x);
void						draw_floor_and_ceiling(t_data *data, int y);
void						draw_sprite(t_data *data, t_sprite_data *sprite);
void					draw_mini_map(t_data *data);

#endif // DRAW_H
