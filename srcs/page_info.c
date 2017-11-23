/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 17:17:21 by amoinier          #+#    #+#             */
/*   Updated: 2017/11/23 19:07:31 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

unsigned int 	get_page_size(size_t size)
{
	unsigned int i;

	i = 1;
	if (size <= TINY_SIZE)
		return ((int)TINY);
	else if (size <= SMALL_SIZE)
		return ((int)SMALL);
	else
	{
		while ((size_t)(getpagesize() * i) < size + sizeof(t_page) + sizeof(t_header))
			i++;
		printf("TEST %d %lu %lu %lu TEST\n", getpagesize() * i, size, sizeof(t_page), sizeof(t_header));
		return (getpagesize() * i);
	}
}

int		get_page_type(size_t size)
{
	if (size <= TINY_SIZE)
		return (0);
	else if (size <= SMALL_SIZE)
		return (1);
	else
		return (2);
}
