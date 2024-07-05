/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 09:51:36 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/04 17:28:06 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	ft_validate_input(int argc, char ***argv)
{
	if (argc != 2)
		return (printf("Usage: ./cub3d <mapname.cub>\n"), false);
	if (ft_strlen((*argv)[1]) <= 4 || ft_strrncmp(".cub", (*argv)[1], 4) != 0)
		return (printf("Error: Incorrect number of arguments\n"), false);
	return (true);
}
