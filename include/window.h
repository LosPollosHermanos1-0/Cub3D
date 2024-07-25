/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:12:48 by jmoritz           #+#    #+#             */
/*   Updated: 2024/06/20 19:12:59 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "cub3d.h"

# define WINDOW_H_INIT 800
# define WINDOW_W_INIT 1200

# define MINI_IMAGE_H 300
# define MINI_IMAGE_W 300

# define MINI_SCALE 10

# define DOOR_ICON_H 50
# define DOOR_ICON_W 50

typedef struct s_window {
	mlx_t		*mlx;
	mlx_image_t	*image;
	int32_t		width;
	int32_t		height;
	mlx_image_t	*mini_image;
	int32_t		mini_width;
	int32_t		mini_height;
	mlx_image_t	*door_icon_open;
	mlx_image_t	*door_icon_close;
	int32_t		door_icon_width;
	int32_t		door_icon_height;
}				t_window;

t_window	*init_window(void);

#endif
