/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:21:49 by jmoritz           #+#    #+#             */
/*   Updated: 2024/06/26 14:21:54 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# define TEX_WIDTH 128
# define TEX_HEIGHT 128

typedef enum e_direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST
}					t_direction;

typedef struct s_coordinate
{
	int				x;
	int				y;
}					t_coordinate;

typedef struct s_raycast_data
{
	double			camera_x;
	t_vector_2d		ray_dir;
	t_vector_2d		delta_dist;
	t_coordinate	map;
	t_vector_2d		side_dist;
	double			perp_wall_dist;
	t_coordinate	step;
	int				hit;
	int				side;
	int				line_height;
}					t_raycast_data;

typedef struct s_wall_rendering_data
{
	int				tex_num;
	int				tex_x;
	int				tex_y;
	double			wall_x;
	double			draw_start;
	double			draw_end;
	double			step;
	double			tex_pos;
}					t_wall_rendering_data;

void				draw_line(mlx_image_t *img, t_vector_2d start,
						t_vector_2d end, uint32_t color);
void				draw_line_vector(mlx_image_t *img, t_vector_2d start,
						t_vector_2d direction, uint32_t color);
void				draw_rays(void);
uint32_t			get_pixel(const mlx_texture_t *texture, uint32_t x,
						uint32_t y);
void				draw_walls(const t_data *data, const t_raycast_data *rd,
						const int x);
void draw_floor(t_data *data, int y);

#endif // DRAW_H
