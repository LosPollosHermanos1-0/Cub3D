/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:06:38 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/01 13:00:52 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

bool	ft_get_rgb(char **line, int ***rgb_ptr)
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
		return (printf("Error: could not split color\n"), false);
	rgb_arr = ft_calloc(sizeof(int), 3);
	i = -1;
	while (rgb_str[++i])
	{
		if ((bool)ft_is_str_digit(rgb_str[i]) == false)
			return (printf("Error: color must be a number\n"), false);
		rgb_arr[i] = ft_atoi(rgb_str[i]);
		if (rgb_arr[i] < 0 || rgb_arr[i] > 255)
			return (printf("Error: rgb must be between 0 and 255\n"), false);
	}
	if (ft_strncmp(direction, "F", 1) == 0)
		index = 0;
	else if (ft_strncmp(direction, "C", 1) == 0)
		index = 1;
	else
		return (printf("Error: invalid color direction\n"), false);
	if ((*rgb_ptr)[index])
		return (printf("Error: color direction encountered twice\n"), false);
	(*rgb_ptr)[index] = rgb_arr;
	return (true);
}
