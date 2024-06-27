/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:06:38 by lzipp             #+#    #+#             */
/*   Updated: 2024/06/27 18:30:06 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

bool	ft_get_rgb_arr(char **line, int **colors_ptr)
{
	char	*color;
	char	direction[2];
	char	**rgb_str;
	int		i;

	ft_memmove(direction, *line, 1);
	direction[1] = '\0';
	color = ft_strtrim(*line + 1, " ");
	rgb_str = ft_split(color, ',');
	if (!rgb_str)
		return (perror("Error: could not split color"), false);
	i = -1;
	while (rgb_str[++i])
	{
		rgb_str = ft_strtrim_in_place(rgb_str, " ");
		if (ft_isdigit(rgb_str[i]) == false)
			return (perror("Error: color must be a number"), false);
	}
	if (ft_strncmp)
	{
		
	}

	return (true);
}
