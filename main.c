/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safiraja <safiraja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 09:39:16 by safiraja          #+#    #+#             */
/*   Updated: 2026/09/22 09:12:11 by safiraja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


// int main(int argc, char **argv)
// {
//     t_config cfg;
//     if(argc != 9)
//     {    
//         if (parse_args(argc, argv, &cfg) != 0)
//             return 1;
//         return 0;
//     }
// }

#include <stdio.h>

void test_atoi(const char *input)
{
    long result;
    int ret;

    ret = ft_atoi_strict(input, &result);
    if (ret == 0)
        printf("\"%s\" -> succès, valeur = %ld\n", input, result);
    else
        printf("\"%s\" -> rejeté\n", input);
}

int main(void)
{
    test_atoi("123");
    test_atoi("-5");
    test_atoi("+42");
    test_atoi("");
    test_atoi("12a");
    test_atoi("0");
    test_atoi("99999999999999999999");   // doit dépasser LONG_MAX
    test_atoi("9223372036854775807");    // LONG_MAX exact, doit réussir
    return 0;
}