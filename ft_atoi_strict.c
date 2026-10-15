/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_strict.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safiraja <safiraja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 09:11:52 by safiraja          #+#    #+#             */
/*   Updated: 2026/10/13 08:33:07 by safiraja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "codexion.h"

int ft_atoi_strict(const char *s, long *out)
{
    int digit;
    long result = 0;
    int sign = 1;

    while(*s == ' ' || (*s >= 9 && *s <= 13))
        s++;
    if(*s == '-' || *s == '+')
    {
        if (*s == '-')
            return -1;
        s++;
    }
    if(!(*s >= '0' && *s <= '9'))
    {
        return -1;
    }
    digit = *s - '0';

    while((*s >= '0') && (*s <= '9')) {
        if(result > (LONG_MAX - digit) / 10)
            return -1;
        result = result * 10 + digit;
        s++;
    }
    if(*s != '\0')
    {
        return -1;
    }
    *out = result * sign;
    return 0;
}