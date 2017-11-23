/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:06:54 by amoinier          #+#    #+#             */
/*   Updated: 2017/11/23 16:02:49 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_page 	g_pages_array[3] = {
	{0, '1', NULL, NULL, NULL},
	{0, '1', NULL, NULL, NULL},
	{0, '1', NULL, NULL, NULL}
};

static int 		init_global(size_t size)
{
	int 	page_type;

	page_type = get_page_type(size);
	if (!g_pages_array[page_type].mem)
	{
		printf("CREATE - mem\n");
		printf("%d\n", get_page_size(size));
		if (!(g_pages_array[page_type].mem = alloc_mmap(get_page_size(size))))
			return (-1);
	}
	if (!g_pages_array[page_type].init)
	{
		printf("CREATE - Init\n");
		g_pages_array[page_type].init = g_pages_array[page_type].mem;
		g_pages_array[page_type].init->free = '1';
		g_pages_array[page_type].init->size = 0;
		g_pages_array[page_type].init->mem = (void *)g_pages_array[page_type].init + sizeof(t_header);
		g_pages_array[page_type].init->space = get_page_size(size) - sizeof(t_header);
		g_pages_array[page_type].init->next = NULL;
		printf("CREATE - Init - Free Space = %d\n", g_pages_array[page_type].init->space);
	}

	return (page_type);
}

static t_header *findPlace(t_page *pages, size_t size)
{
	int 		i;
	t_header	*tmp;

	i = 0;
	printf("--- PAGES MAX SIZE = %d %lu ---\n", pages->max_space_size, (size + sizeof(t_header)));
	if (pages->space_left == '0' || (double)(pages->max_space_size - (size + sizeof(t_header))) <= 0)
	{
		if (!pages->next)
		{
			printf("FINDPLACE - No space, try to create new page\n");
			if (init_new_page(pages, size))
				return (findPlace(pages->next, size));
			else
				return (NULL);
		}
		else
		{
			//printf("FINDPLACE - No space, go to next page\n");
			return (findPlace(pages->next, size));
		}
	}
	else
	{
		if (pages->init)
		{
			printf("FINDPLACE - Space, Init exist\n");
			tmp = pages->init;
			printf("FINDPLACE - Start While\n");
			while (tmp)
			{
				if (tmp->free == '1' && size <= (tmp->size + tmp->space))
				{
					printf("FINDPLACE - Space and free block\n");
					tmp->free = '0';
					tmp->space = (tmp->space + tmp->size) - size;
					tmp->size = size;
					if (pages->max_space_size != 0)
						pages->max_space_size = (pages->max_space_size <= tmp->space ? tmp->space : pages->max_space_size);
					printf("Space left - %d\n", tmp->space);
					return (tmp);
				}
				i++;
				if (!tmp->next)
					break ;
				tmp = tmp->next;
			}
			printf("FINDPLACE - (%d) Space and no free block\n", i);
			printf("WESH %u - %zu - %d\n", tmp->space, size, (int)(tmp->space - size));
			if ((int)(tmp->space - size) <= 0)
			{
				printf("i == BLOCK_NBR\n");
				pages->max_space_size = tmp->space;
				pages->space_left = '0';
				return findPlace(pages, size);
			}
			else
			{
				printf("i != BLOCK_NBR\n");
				printf("Space left - %d\n", tmp->space);
				init_new_block(pages, tmp, size);
				printf("X Space left - %d\n", tmp->next->space);
				return (tmp->next);
			}
		}
		else
		{
			return (NULL);
		}
	}
}

void 		*malloc(size_t size)
{
	int 	page_type;
	t_header	*test;

	page_type = init_global(size);
	test = findPlace(&g_pages_array[page_type], size);

	return (test->mem);
}
