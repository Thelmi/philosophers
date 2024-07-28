/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhelmy <mrhelmy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:22:19 by mrhelmy           #+#    #+#             */
/*   Updated: 2024/07/29 00:46:28 by mrhelmy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int input_parsing(char **str)
{
    int i;

    i = 1;
    while (str[i])
    {
        if (ft_isnum(str[i]) == 0)
            return (0);
        i++;
    }
    if (ft_atoi(str[1]) > 200) //double check if 200 is the max number of philos or not
        return (0);
    return (1);
}
