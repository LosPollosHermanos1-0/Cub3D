/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:49:56 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/25 16:49:42 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifdef IS_BONUS
#  define BONUS 1
# else
#  define BONUS 0
# endif

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>

# include "lib.h"
# include "MLX42.h"
# include "window.h"
# include "static.h"
# include "input.h"
# include "player.h"
# include "opponent.h"
# include "draw.h"
# include "utils.h"
# include "parsing.h"

# ifndef LEAKS
#  define LEAKS 0
# endif

#endif
