/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 11:39:16 by ldutriez          #+#    #+#             */
/*   Updated: 2020/01/09 14:16:37 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		main(int argc, char *argv[])
{
	int		letters[255];
	int		index;
	int		l_index;

	index = 0;
	l_index = 0;
	if (argc == 3)
	{
		while (index < 255)
			letters[index++] = 0;
		index = 0;
		while (argv[2][index])
		{
			if (letters[(unsigned char)argv[2][index]] == 0)
				letters[(unsigned char)argv[2][index]] = 1;
			index++;
		}
		index = 0;
		while (argv[1][index])
		{
			if (letters[(unsigned char)argv[1][index]] == 1)
			{
				letters[(unsigned char)argv[1][index]] = 2;
				write(1, &(argv[1][index]), 1);
			}
			index++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
