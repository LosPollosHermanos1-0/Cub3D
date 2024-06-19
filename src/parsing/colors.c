/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:06:38 by lzipp             #+#    #+#             */
/*   Updated: 2024/06/19 16:06:46 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

bool	ft_get_rgb_arr(char **line, int ***colors_ptr)
{
	char	*color;
	char	direction[3];
	char	**rgb_str;
	int		*rgb;

	ft_memmove(direction, *line, 1);
	direction[1] = NULL;
	color = ft_strtrim(*line + 1, " ");
	if (!color)
		return (perror("Error: could not get color"), false);
	rgb_str = ft_split(color, ',');
	free(color);
	if (!rgb_str)
		return (perror("Error: could not split color"), false);
	if (ft_null_terminated_arr_len(rgb_str) != 3)
		return (perror("Error: color must be a single path"), false);
	rgb = (int *)malloc(sizeof(int) * 3);
	if (!rgb)
		return (perror("Error: could not allocate memory for color"), false);
	rgb[0] = ft_atoi(rgb_str[0]);
	rgb[1] = ft_atoi(rgb_str[1]);
	rgb[2] = ft_atoi(rgb_str[2]);
	ft_null_terminated_arr_free(rgb_str);
	return (ft_null_terminated_arr_add(colors_ptr, rgb));
}