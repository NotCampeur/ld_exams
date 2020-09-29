/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 12:00:27 by ldutriez          #+#    #+#             */
/*   Updated: 2020/01/23 12:08:22 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int		main(void)
{
	char **line;
	int	i;

	i = 0;
	line = (char**)malloc(sizeof(char));
	if (line == NULL)
		return (0);
	while ((i = get_next_line(line)) > 0)
	{
		printf("%d | %s\n", i, *line);
	}
	return (0);
}
