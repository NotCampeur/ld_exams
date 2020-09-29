/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 14:46:20 by ldutriez          #+#    #+#             */
/*   Updated: 2020/01/23 17:12:43 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct s_data
{
	int			count;
	int			width_value;
	int			precision;
	int			precision_value;
	char		converter;
}				t_data;

static	t_data data_creator(void)
{
	t_data result;
	
	result.count = 0;
	result.width_value = 0;
	result.precision = 0;
	result.precision_value = 0;
	result.converter = '\0';
	return (result);
}

static	void reset_data(t_data *data)
{
	data->width_value = 0;
	data->precision = 0;
	data->precision_value = 0;
	data->converter = '\0';
}

static int ft_strlen(char *str)
{
	int index;

	index = 0;
	while (str[index])
		index++;
	return (index);
}

static char *ft_strdup(char *str)
{
	char *result;
	int	index;

	index = 0;
	result = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (result == NULL)
		return (NULL);
	while (str[index] != '\0')
	{
		result[index] = str[index];
		index++;
	}
	result[index] = '\0';
	return (result);
}

static int ft_nbr_len(int nbr, int base_len)
{
	int	result;

	result = 1;
	while (nbr >= base_len)
	{
		result++;
		nbr /= base_len;
	}
	return (result);
}

static char *ft_itoa_base(int nbr, char *base,int base_len)
{
	char *result;
	int index;
	int	nbr_len;

	nbr_len = ft_nbr_len(nbr, base_len);
	index = nbr_len;
	result = (char *)malloc(sizeof(char) * (nbr_len + 1));
	if (result == NULL)
		return(NULL);
	result[index] = '\0';
	while (index > 0)
	{
		index--;
		result[index] = base[nbr % base_len];
		nbr /= base_len;
	}
	return(result);
}

static int	ft_atoi(char *str, int *p_index)
{
	int result;
	int index;

	result = 0;
	index = 0;
	while (str[index] != '\0' && str[index] > '0' && str[index] <= '9')
	{
		result *= 10;
		result += ((str[index] - 48) % 10);
		index++;
	}
	(*p_index) += index;
	return (result);
}

static void ft_get_flag(char *format, int *index, t_data *data)
{
	while (format[*index] && format[*index] != 's' &&
							format[*index] != 'd' &&
							format[*index] != 'x')
	{
		if (format[*index] > '0' && format[*index] <= '9')
			data->width_value = ft_atoi(format, index);
		if (format[*index] == '.')
		{
			data->precision = 1;
			(*index)++;
			data->precision_value = ft_atoi(format, index);
		}
	}
	data->converter = format[*index];
}

static char *ft_get_arg(va_list arg, t_data *data)
{
	char *result;

	result = NULL;
	if (data->converter == 's')
		result = ft_strdup(va_arg(arg, char *));
	else if (data->converter == 'x')
		result = ft_itoa_base(va_arg(arg, int), "0123456789abcdef", 16);
	else if (data->converter == 'd')
		result = ft_itoa_base(va_arg(arg, int), "0123456789", 10);
	return(result);
}

int		ft_printf(const char *format, ...)
{
	t_data data;
	int index;
	va_list arg;
	char	*converted;
	
	converted = NULL;
	if (!format)
		return (0);
	data = data_creator();
	index = 0;
	va_start(arg, format);
	while (format[index])
	{
		if (format[index] == '%')
		{
			index++;
			ft_get_flag((char *)format, &index, &data);
			converted = ft_get_arg(arg, &data);
			if (data.precision == 1)
				converted = ft_apply_precision(converted, data);
			if (data.width_value != 0)
				converted = ft_apply_width(converted, data);
			ft_putstr(converted);
			data.count += ft_strlen(converted);
			ft_reset_data(&data);
			free(converted);
		}
		else
		{
			write(1, &format[index], 1);
			data.count++;
		}
		index++;
	}
	va_end(arg);
	return (data.count);
}
