/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 13:00:19 by ldutriez          #+#    #+#             */
/*   Updated: 2020/02/08 11:45:44 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	str_len(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char *sub_str(char *buffer, int start, int end)
{
	char *result;
	int		index;

	index = 0;
	result = (char*)malloc(sizeof(char) * (end - start + 1));
	if (result == NULL)
		return (NULL);
	while (index < end - start)
	{
		result[index] = buffer[start + index];
		index++;
	}
	result[index] = '\0';
	return (result);
}

static char *sub_str_and_free(char *buffer, int start, int end)
{
	char *result;
	int		index;

	index = 0;
	result = (char*)malloc(sizeof(char) * (end - start + 1));
	if (result == NULL)
		return (NULL);
	while (index < end - start)
	{
		result[index] = buffer[start + index];
		index++;
	}
	result[index] = '\0';
	free(buffer);
	return (result);
}

static char *add_suffixe(char *buffer, char *readed)
{
	char *result;
	int index;
	int b_len;
	int r_len;

	b_len = str_len(buffer);
	r_len = str_len(readed);
	result = (char*)malloc(sizeof(char) * (b_len + r_len + 1));
	if (result == NULL)
		return (NULL);
	index = 0;
	while (buffer[index])
	{
		result[index] = buffer[index];
		index++;
	}
	index = 0;
	while (readed[index])
	{
		result[b_len + index] = readed[index];
		index++;
	}
	result[b_len + index] = '\0';
	free(buffer);
	return (result);
}

static int eol(char *buffer)
{
	int i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int		get_next_line(char **line)
{
	static char *buffer = NULL;
	char		readed[BUFFER_SIZE + 1];
	int			read_ret;
	int			index;

	if (line == NULL)
		return (-1);
	if (buffer == NULL)
	{
		buffer = (char*)malloc(sizeof(char));
		if (buffer == NULL)
			return (-1);
		buffer[0] = '\0';
	}
	read_ret = 1;
	index = 0;
	while (eol(buffer) == 0 && read_ret > 0)
	{
		read_ret = read(0, readed, BUFFER_SIZE);
		if (read_ret < 0)
		{
			free(buffer);
			buffer = NULL;
			return (-1);
		}
		else
		{
			readed[read_ret] = '\0';
			buffer = add_suffixe(buffer, readed);
		}
	}
	while (buffer[index] != '\0' && buffer[index] != '\n')
		index++;
	*line = sub_str(buffer, 0, index);
	if (buffer[index] != '\0')
		buffer = sub_str_and_free(buffer, index + 1, str_len(buffer));
	if (read_ret == 0)
	{
		free(buffer);
		buffer = NULL;
		return (0);
	}
	return (1);
}
