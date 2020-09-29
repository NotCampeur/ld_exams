/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 10:04:29 by ldutriez          #+#    #+#             */
/*   Updated: 2020/01/23 17:23:59 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"

int		main(int argc, char *argv[])
{
	int		letters[255];
	int		i;

	i = 0;
	while (i < 255)
		letters[i++] = 0;
	i = 0;
	if (argc == 3)
	{
		while (argv[2][i] != '\0')
		{
			if (letters[(unsigned char)argv[2][i]] == 0)
				letters[(unsigned char)argv[2][i]] = 1;
			i++;
		}
		i = 0;
		while (argv[1][i] != '\0')
		{
			if (letters[(unsigned char)argv[1][i]] == 1)
			{
				letters[(unsigned char)argv[1][i]] = 2;
				write(1, argv[1] + i, 1);
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
	}
