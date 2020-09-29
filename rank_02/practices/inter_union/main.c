/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 14:41:00 by ldutriez          #+#    #+#             */
/*   Updated: 2020/01/09 15:17:36 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		is_present(char *lettres, char c)
{
	int i;

	i = 0;
	while (lettres[i])
	{
		if (lettres[i] == c)
			return (1);
	 i++;
	}
	return (0);
}

int		main(int argc, char *argv[])
{
	int letters[255];
	char lettres[255];
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < 255)
		letters[i++] = 0;
	i = 0;
	if (argc == 3)
	{
		while (argv[2][i])
		{
			if (letters[(unsigned char)argv[2][i]] == 0)
				letters[(unsigned char)argv[2][i]] = 1;
			i++;
		}
		i = 0;
		while (argv[1][i])
		{
			if (letters[(unsigned char)argv[1][i]] == 1)
			{
				letters[(unsigned char)argv[1][i]] = 2;
				write(1, &(argv[1][i]), 1);
			}
			i++;
		}
		write(1, "\n", 1);
	
		i = 0;
		while (i < 255)
			lettres[i++] = 0;
		i = 0;
		while (argv[1][i])
		{
			if (!is_present(lettres, argv[1][i]))
			{
				write(1, &(argv[1][i]), 1);
				lettres[j++] = argv[1][i];
			}
			i++;
		}
		i = 0;
		while (argv[2][i])
		{
			if (!is_present(lettres, argv[2][i]))
			{
				write(1, &(argv[2][i]), 1);
				lettres[j++] = argv[2][i];
			}
			i++;
		}
	}
	return (0);
}
