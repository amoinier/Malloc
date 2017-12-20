/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_element.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 17:10:38 by amoinier          #+#    #+#             */
/*   Updated: 2017/11/23 19:11:43 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			init_new_block(t_page *page, t_header *header, size_t size)
{
	t_header	*tmp;

	tmp = header->next;
	header->next = (t_header *)(header->mem + header->size);
	header->next->mem = (void *)header->next + sizeof(t_header);
	header->next->space = (!tmp ? header->space - sizeof(t_header) - size :
	tmp->space);
	header->next->next = tmp;
	header->next->size = size;
	header->next->page = page;
	header->space = 0;
	page->max_space_size = header->next->space;
}

void			*init_new_page(t_page *pages, size_t size)
{
	if (!(pages->next = (t_page *)alloc_mmap(get_page_size(size))))
		return (NULL);
	else
	{
		pages->next->max_space_size = get_page_size(size) - sizeof(t_page);
		pages->next->mem = (void *)pages->next + sizeof(t_page);
		pages->next->next = NULL;
		pages->next->init = (t_header *)(pages->next->mem);
		pages->next->init->size = 0;
		pages->next->init->page = pages->next;
		pages->next->init->space = get_page_size(size) - sizeof(t_page) - sizeof(t_header);
		pages->next->init->mem = (void *)pages->next->init + sizeof(t_header);
		pages->next->init->next = NULL;
		return (pages);
	}
}
