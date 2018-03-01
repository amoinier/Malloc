/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:08:10 by amoinier          #+#    #+#             */
/*   Updated: 2018/03/01 19:11:33 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_header		*check_before_realloc(void *ptr, size_t size)
{
	t_header		*header;

	if (!ptr)
		return (malloc(size));
	header = find_ptr(ptr);
	if (!header || !header->mem || !header->page)
		return (NULL);
	return (header);
}

void				*realloc(void *ptr, size_t size)
{
	void		*dest;
	t_header	*header;

	if (!(header = check_before_realloc(ptr, size)))
	{
		return (header);
	}
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
