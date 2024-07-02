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
}				t_direction;

typedef struct s_raycast_data
{
	double		camera_x;
	t_vector_2d	ray_dir;
	t_vector_2d	delta_dist;
	int			map_x;
	int			map_y;
	t_vector_2d	side_dist;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int		line_height;
}				t_raycast_data;

void			draw_line(mlx_image_t *img, t_vector_2d start, t_vector_2d end,
					uint32_t color);
void			draw_line_vector(mlx_image_t *img, t_vector_2d start,
					t_vector_2d direction, uint32_t color);
void			draw_rays(void);
uint32_t get_pixel(const mlx_texture_t* texture, uint32_t x, uint32_t y);

#endif // DRAW_H
