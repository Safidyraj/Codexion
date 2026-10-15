/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_strict.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safiraja <safiraja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 09:11:52 by safiraja          #+#    #+#             */
/*   Updated: 2026/09/22 12:50:57 by safiraja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "codexion.h"

static int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	ft_atoi_strict(const char *s, long *out)
{
	long	result;
	int		digit;

	result = 0;
	while (is_space(*s))
		s++;
	if (*s == '+')
		s++;
	if (*s < '0' || *s > '9')
		return (-1);
	while (*s >= '0' && *s <= '9')
	{
		digit = *s - '0';
		if (result > (LONG_MAX - digit) / 10)
			return (-1);
		result = result * 10 + digit;
		s++;
	}
	if (*s != '\0')
		return (-1);
	*out = result;
	return (0);
}
