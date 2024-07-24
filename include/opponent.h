/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opponent.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:20:09 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/24 11:20:14 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPPONENT_H
#define OPPONENT_H

typedef enum e_opponent_state
{
    OPPONENT_IDLE,
    OPPONENT_WALKING,
    OPPONENT_ATTACKING,
    OPPONENT_DEAD
}				t_opponent_state;

#endif //OPPONENT_H
