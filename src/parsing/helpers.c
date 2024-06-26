/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:01:57 by lzipp             #+#    #+#             */
/*   Updated: 2024/06/26 14:18:24 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

bool	ft_wrong_char_inside(char **str)
{
	int		i;

	i = -1;
	while (str && (*str)[++i])
	{
		printf("char: %c\n", (*str)[i]);
		if ((*str)[i] != 'N' && (*str)[i] != 'O' && (*str)[i] != 'S'
			&& (*str)[i] != 'W' && (*str)[i] != 'E' && (*str)[i] != 'A'
			&& (*str)[i] != 'F' && (*str)[i] != 'C'
			&& (*str)[i] != ' ' && (*str)[i] != ',' && (*str)[i] != '/'
			&& (*str)[i] != '.' && (*str)[i] != '\n'
			&& (*str)[i] != '0' && (*str)[i] != '1' && (*str)[i] != '2'
			&& (*str)[i] != '3' && (*str)[i] != '4' && (*str)[i] != '5'
			&& (*str)[i] != '6' && (*str)[i] != '7' && (*str)[i] != '8'
			&& (*str)[i] != '9')
			return (true);
		// if ((*str)[i])
	}
	return (false);
}
