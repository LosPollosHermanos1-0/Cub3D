/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:06:38 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/08 17:29:41 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_strs_len(char **rgb_str) {
	int	i;

	i = 0;
	while (rgb_str[i])
		i++;
	return (i);
}

bool ft_get_rgb(char **line, t_rgb_color **f_and_c_color)
{
	char	*color;
	char	direction[2];
	char	**rgb_str;
	int		index;
	t_rgb_color new_color;

	ft_memmove(direction, *line, 1);
	direction[1] = '\0';
	color = ft_strtrim(*line + 1, " ");
	rgb_str = ft_split(color, ',');
	free(color);
	if (rgb_str == NULL)
		return (printf("Error: could not split color\n"), false);
	if (ft_strs_len(rgb_str) != 3)
		return (ft_free_2d_arr((void**)rgb_str), printf("Error: color must have 3 values\n"), false);
	new_color.r = ft_atoi(rgb_str[0]);
	new_color.g = ft_atoi(rgb_str[1]);
	new_color.b = ft_atoi(rgb_str[2]);
	if (!ft_is_str_digit(rgb_str[0]) || !ft_is_str_digit(rgb_str[1]) || !ft_is_str_digit(rgb_str[2]))
		return (ft_free_2d_arr((void**)rgb_str), printf("Error: color must be a number\n"), false);
	ft_free_2d_arr((void**)rgb_str);
	if (new_color.r < 0 || new_color.r > 255 || new_color.g < 0 || new_color.g > 255 || new_color.b < 0 || new_color.b > 255)
		return (printf("Error: rgb must be between 0 and 255\n"), false);
	if (ft_strncmp(direction, "F", 1) == 0)
		index = 0;
	else if (ft_strncmp(direction, "C", 1) == 0)
		index = 1;
	else
		return (printf("Error: invalid color direction\n"), false);
	if (f_and_c_color[index])
		return (printf("Error: color direction encountered twice\n"), false);
	f_and_c_color[index] = &new_color;
	return (true);
}
