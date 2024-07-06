/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:51:34 by jmoritz           #+#    #+#             */
/*   Updated: 2024/06/27 14:51:39 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

void	arrow_key_hook(mlx_key_data_t keydata, void *param);
void	wasd_key_input(void *data);
void	key_handler(mlx_key_data_t keydata, void *data);
void	resize_handler(int32_t width, int32_t height, void *d);
void	center_mouse(const t_data *data);
void	toogle_mouselock_and_visability(t_data *data);

void	mouse_move_callback(double xpos, double ypos, void *param);
void	mouse_click_handler(mouse_key_t button, action_t action,
			modifier_key_t mods, void *p);

#endif
