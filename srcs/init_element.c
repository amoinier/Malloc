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

void 		init_new_block(t_page *pages, t_header *header, size_t size)
{
	t_header 	*tmp;

	printf("XXX %d - %zu - %zu XXX\n", header->space, sizeof(*header->next), size);

	tmp = header->next;
	header->next = (t_header *)(header->mem + header->size);
	header->next->mem = (void *)header->next + sizeof(t_header);
	header->next->space = (!tmp ? header->space - sizeof(t_header) - size : tmp->space);
	header->next->next = tmp;
	header->next->size = size;
	header->next->free = '0';
	header->space = 0;
	pages->max_space_size = header->next->space;
}

void 		*init_new_page(t_page *pages, size_t size)
{
	if (!(pages->next = (t_page *)alloc_mmap(get_page_size(size))))
		return (NULL);
	else
	{
		pages->next->max_space_size = get_page_size(size) - sizeof(t_page);
		pages->next->mem = (void *)pages->next + sizeof(t_page);
		pages->next->next = NULL;
		pages->next->init = (t_header *)(pages->next->mem);

		pages->next->init->free = '1';
		pages->next->init->size = 0;
		pages->next->init->space = get_page_size(size) - sizeof(t_page);
		pages->next->init->mem = (void *)pages->init + sizeof(t_header);
		pages->next->init->next = NULL;
		printf("** %d - %lu - %lu - %d - %d **\n", get_page_size(size), sizeof(t_page), sizeof(t_header), pages->next->init->space, pages->next->max_space_size);
		return (pages);
	}
}
