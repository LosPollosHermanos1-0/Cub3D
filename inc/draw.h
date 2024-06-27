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
#define DRAW_H

void	draw_line(mlx_image_t *img, t_vector_2d start, t_vector_2d end, uint32_t color);
void draw_line_vector(mlx_image_t *img, t_vector_2d start, t_vector_2d direction, uint32_t color);

#endif //DRAW_H
