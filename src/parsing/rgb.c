/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:06:38 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/22 13:04:48 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char		**get_rgb_str(char **line);
static int		ft_strs_len(char **rgb_str);
t_rgb_color		*create_and_validate_color(char **rgb_str);

bool	ft_get_rgb(char **line, t_rgb_color **f_and_c_color)
{
	char		direction[2];
	char		**rgb_str;
	int			index;
	t_rgb_color	*new_color;

	rgb_str = get_rgb_str(line);
	if (rgb_str == NULL)
		return (false);
	new_color = create_and_validate_color(rgb_str);
	ft_free_2d_arr((void **)rgb_str);
	if (new_color == NULL)
		return (false);
	ft_memmove(direction, *line, 1);
	direction[1] = '\0';
	if (ft_strncmp(direction, "F", 1) == 0)
		index = 0;
	else if (ft_strncmp(direction, "C", 1) == 0)
		index = 1;
	else
		return (printf("Error: invalid color or direction\n"), false);
	if (f_and_c_color[index])
		return (printf("Error: color or direction encountered twice\n"),
			false);
	f_and_c_color[index] = new_color;
	return (true);
}

static char	**get_rgb_str(char **line)
{
	char	*color;
	char	**rgb_str;

	color = ft_strtrim(*line + 1, " ");
	rgb_str = ft_split(color, ',');
	free(color);
	if (rgb_str == NULL)
		return (printf("Error: could not split color\n"), NULL);
	if (!ft_is_str_digit(rgb_str[0])
		|| !ft_is_str_digit(rgb_str[1])
		|| !ft_is_str_digit(rgb_str[2]))
		return (ft_free_2d_arr((void **)rgb_str),
			printf("Error: color must be a number\n"), NULL);
	if (ft_strs_len(rgb_str) != 3)
		return (ft_free_2d_arr((void **)rgb_str),
			printf("Error: rgb color must have 3 values\n"), NULL);
	return (rgb_str);
}

t_rgb_color	*create_and_validate_color(char **rgb_str)
{
	t_rgb_color	*new_color;

	new_color = malloc(sizeof(t_rgb_color));
	if (new_color == NULL)
	{
		ft_free_2d_arr((void **)rgb_str);
		printf("Error: could not create new color\n");
		return (NULL);
	}
	new_color->r = ft_atoi(rgb_str[0]);
	new_color->g = ft_atoi(rgb_str[1]);
	new_color->b = ft_atoi(rgb_str[2]);
	if (new_color->r < 0 || new_color->r > 255
		|| new_color->g < 0 || new_color->g > 255
		|| new_color->b < 0 || new_color->b > 255)
	{
		free(new_color);
		printf("Error: rgb values must be between 0 and 255\n");
		return (NULL);
	}
	return (new_color);
}

static int	ft_strs_len(char **rgb_str)
{
	int	i;

	i = 0;
	while (rgb_str[i])
		i++;
	return (i);
}
