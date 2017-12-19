/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:07:41 by amoinier          #+#    #+#             */
/*   Updated: 2017/11/22 15:22:54 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static char		*reverse_string(char *str)
{
	char		tmp;
	int			j;
	int			size;

	j = 0;
	size = ft_strlen(str) - 1;
	while (str[j * 2])
	{
		tmp = str[j];
		str[j] = str[size - j];
		str[size - j] = tmp;
		j++;
	}
	return (str);
}

static char		*change_base(intptr_t addr, int base)
{
	char		char_base[16];
	char		*result;
	int			tmp;
	int			j;

	char_base = "0123456789ABCDEF";
	j = 0;
	tmp = 0;
	if (!(result = (char *)malloc(sizeof(char) * 17)))
		return (NULL);
	while (addr != 0)
	{
		tmp = addr % base;
		result[j] = char_base[tmp];
		addr /= base;
		j++;
	}
	result[j] = '\0';
	result = reverse_string(result);
	return (result);
}

void			print_memory(const void *addr)
{
	char		*str_addr;

	str_addr = change_base((intptr_t)addr, 16);
	ft_putstr("0x");
	ft_putstr(str_addr);
	free(str_addr);
	return ;
}
