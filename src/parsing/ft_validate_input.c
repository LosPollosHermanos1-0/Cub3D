/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 09:51:36 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/04 15:27:39 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/parsing.h"

bool	ft_validate_input(int argc, char ***argv)
{
	if (argc != 2)
		return (printf("Usage: ./cub3d <mapname.cub>\n"), false);
	if (ft_strlen((*argv)[1]) <= 4 || ft_strrncmp(".cub", (*argv)[1], 4) != 0)
		return (printf("Error: Incorrect number of arguments\n"), false);
	return (true);
}

// test
// #include "../../inc/parsing.h"
// int main(void)
// {
// 	char *c1[] = {"./cub3d", "mapname.cub"};
// 	char *c2[] = {"./cub3d", "a.cub"};
// 	char *w1[] = {"./cub3d"};
// 	char *w2[] = {"./cub3d", "mapname"};
// 	char *w3[] = {"./cub3d", "mapname.cu"};
// 	char *w4[] = {"./cub3d", "mapname.cub", "mapname2.cub"};

// }
