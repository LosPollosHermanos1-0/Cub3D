/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:06:38 by lzipp             #+#    #+#             */
/*   Updated: 2024/06/28 12:25:30 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

bool	ft_get_color(char **line, int **rgb_ptr)
{
	char	*color;
	char	direction[2];
	char	**rgb_str;
	int		index;
	int		*rgb_arr;
	int		i;

	ft_memmove(direction, *line, 1);
	direction[1] = '\0';
	color = ft_strtrim(*line + 1, " ");
	rgb_str = ft_split(color, ',');
	if (!rgb_str)
		return (perror("Error: could not split color"), false);
	rgb_arr = ft_calloc(sizeof(int), 4);
	i = -1;
	while (rgb_str[++i])
	{
		if ((bool)ft_is_str_digit(rgb_str[i]) == false)
			return (perror("Error: color must be a number"), false);
		rgb_arr[i] = ft_atoi(rgb_str[i]);
		if (rgb_arr[i] < 0 || rgb_arr[i] > 255)
			return (perror("Error: rgb must be between 0 and 255"), false);
	}
	if (ft_strncmp(direction, "F", 1) == 0)
		index = 0;
	else if (ft_strncmp(direction, "C", 1) == 0)
		index = 1;
	else
		return (perror("Error: invalid color direction"), false);
	if (*rgb_ptr[index])
		return (perror("Error: color direction encountered twice"), false);
	rgb_ptr[index] = rgb_arr;
	return (true);
}
