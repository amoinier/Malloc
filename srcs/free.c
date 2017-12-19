/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:07:41 by amoinier          #+#    #+#             */
/*   Updated: 2017/11/22 15:22:54 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_page g_pages_array[3];

static	t_header	*find_prev_header(t_page *page, t_header *block)
{
	t_header		*tmp;

	tmp = page->init;
	while (tmp && tmp->next != block && tmp != block)
		tmp = tmp->next;
	return (tmp);
}

void				free(void *ptr)
{
	t_header		*header;
	t_header		*prev;

	header = (t_header *)(ptr - sizeof(t_header));
	prev = find_prev_header(header->page, header);
	if (prev)
	{
		if (prev != header)
		{
			prev->next = header->next;
			prev->space += sizeof(t_header) + header->size + header->space;
			header->page->max_space_size = (header->page->max_space_size <
			prev->space ? prev->space : header->page->max_space_size);
			ft_bzero(header, sizeof(t_header) + header->size);
		}
		else
		{
			header->space += header->size;
			header->page->max_space_size += header->size;
			ft_bzero(header->mem, header->size);
			header->size = 0;
		}
	}
	return ;
}
