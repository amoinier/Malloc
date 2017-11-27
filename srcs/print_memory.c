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
	char 	result[16];
	int 	i;
	int 	j;

	i = 0;
	j = 2;
	result[0] = "0";
	result[1] = "x";
	while (addr != 0)
	{
		if (addr < 15)
		{
			result[j];
		}
		j++;
	}
}

void	print_memory(const void *addr, size_t size)
{
	printf("ADDR: %p(%ld) - size: %zu\n", addr, (intptr_t)addr, size);
	return ;
}
