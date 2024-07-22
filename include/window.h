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


#ifndef INIT_WINDOW_H
#define INIT_WINDOW_H

# define WINDOW_H_INIT 800
# define WINDOW_W_INIT 1200

typedef struct s_window {
    mlx_t *mlx;
    mlx_image_t *image;
    int32_t width;
    int32_t height;
} t_window;

t_window	*init_window();

#endif
