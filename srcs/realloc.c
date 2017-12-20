/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:08:10 by amoinier          #+#    #+#             */
/*   Updated: 2017/11/22 15:23:06 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*realloc(void *ptr, size_t size)
{
	void		*dest;
	t_header	*header;

	header = (t_header *)(ptr - sizeof(t_header));
	if (!header || !header->mem || !header->page)
		return (NULL);
	if (header->size + header->space < size)
	{
		if (!(dest = (void *)malloc(size + 1)))
			return (NULL);
		dest = ft_memcpy(dest, ptr, header->size);
		if (ptr != dest)
			free(ptr);
	}
	else
	{
		dest = ptr;
		header->space = (header->size + header->space) - size;
		header->size = size;
	}
	return (dest);
}
