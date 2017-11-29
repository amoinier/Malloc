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

static char 	*change_base(intptr_t addr, int base)
{
	char 	char_base[16] = "0123456789ABCDEF";
	char 	*result;
	int 	tmp;
	int 	j;

	j = 2;
	result[0] = '0';
	result[1] = 'x';
	tmp = 0;
	if (!(result = (char *)malloc(sizeof(char) * 19)))
		return (NULL);
	while (addr != 0)
	{
		tmp = addr % base;
		result[j] = char_base[tmp];
		addr /= base;
		j++;
	}
	result[j] = '\0';
	j = 0;
	// while (j < ft_strlen(result))
	// {
    //
	// }

	printf("- %s\n", result);
	return (NULL);
}

void	print_memory(const void *addr, size_t size)
{
	change_base((intptr_t)addr, 16);
	printf("ADDR: %p(%ld) - size: %zu\n", addr, (intptr_t)addr, size);
	return ;
}
