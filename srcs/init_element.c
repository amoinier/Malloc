/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_element.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 17:10:38 by amoinier          #+#    #+#             */
/*   Updated: 2017/11/22 20:17:28 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void 		init_new_block(t_header *header, size_t size)
{
	printf("XXX %d - %zu - %zu XXX\n", header->space, sizeof(*header->next), size);
	printf("! MEMORY TEST ! %zu %zu %zu ! MEMORY TEST\n", sizeof(&header->next), sizeof(header->next), sizeof(*header->next));

	header->next = (t_header *)(header->mem + header->size);
	header->next->mem = ((header->mem + header->size) + sizeof(*header->next));
	header->next->space = header->space - sizeof(*header->next) - size - 10;
	header->next->next = NULL;
	header->next->size = size;
	header->next->free = '0';
	header->space = 0;

}

void 		*init_new_page(t_page *pages, size_t size)
{
	if (!(pages->next = (t_page *)alloc_mmap(get_page_size(size))))
		return (NULL);
	else
	{
		pages->next->space_left = '1';
		pages->next->mem = (void *)(pages->next + sizeof(*pages->next));
		pages->next->next = NULL;
		pages->next->init = (t_header *)(pages->next->mem);

		pages->next->init->free = '1';
		pages->next->init->size = size;
		pages->next->init->space = get_page_size(size) - sizeof(*pages->next) - sizeof(*pages->next->init) - size;
		pages->next->init->mem = (void *)(pages->init + sizeof(*pages->init));
		pages->next->init->next = NULL;
		return (pages);
	}
}
