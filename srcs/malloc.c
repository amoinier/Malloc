/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:06:54 by amoinier          #+#    #+#             */
/*   Updated: 2017/11/22 20:17:56 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_page 	g_pages_array[3] = {
	{'1', NULL, NULL, NULL},
	{'1', NULL, NULL, NULL},
	{'1', NULL, NULL, NULL}
};

static int 		init_global(size_t size)
{
	int 	page_type;

	page_type = get_page_type(size);
	if (!g_pages_array[page_type].mem)
	{
		printf("CREATE - mem\n");
		if (!(g_pages_array[page_type].mem = alloc_mmap(get_page_size(size))))
			return (-1);
	}
	if (!g_pages_array[page_type].init)
	{
		printf("CREATE - Init\n");
		g_pages_array[page_type].init = g_pages_array[page_type].mem;
		g_pages_array[page_type].init->free = '1';
		g_pages_array[page_type].init->size = 0;
		g_pages_array[page_type].init->mem = (void *)(g_pages_array[page_type].init + sizeof(*g_pages_array[page_type].init));
		g_pages_array[page_type].init->space = get_page_size(size) - sizeof(*g_pages_array[page_type].init);
		g_pages_array[page_type].init->next = NULL;
		printf("! MEMORY TEST ! %zu %zu %zu ! MEMORY TEST\n", sizeof(&g_pages_array[page_type].init), sizeof(g_pages_array[page_type].init), sizeof(*g_pages_array[page_type].init));
		printf("CREATE - Init - Free Space = %d\n", g_pages_array[page_type].init->space);
	}

	return (page_type);
}

static t_header *findPlace(t_page *pages, size_t size)
{
	int 		i;
	t_header	*tmp;

	i = 0;
	if (pages->space_left == '0')
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
			printf("Start While\n");
			while (tmp)
			{
				if (tmp->free == '1' && size <= (tmp->size + tmp->space))
				{
					printf("FINDPLACE - Space and free block\n");
					printf("Space left - %d %d %zu\n", tmp->space, tmp->size, size);
					tmp->space = (tmp->space + tmp->size) - size;
					tmp->size = size;
					tmp->free = '0';
					printf("Space left - %d\n", tmp->space);
					return (tmp);
				}
				i++;
				if (!tmp->next)
					break ;
				tmp = tmp->next;
			}
			printf("FINDPLACE - Space and no free block\n");
			if ((double)(tmp->space - size) >= 0)
			{
				printf("i == BLOCK_NBR\n");
				pages->space_left = '0';
				return findPlace(pages, size);
			}
			else
			{
				printf("i != BLOCK_NBR\n");
				printf("Space left - %d\n", tmp->space);
				init_new_block(tmp, size);
				printf("X Space left - %d %d %zu\n", tmp->space, tmp->next->space, size);
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

	printf("%zu SIZE TINY %zu\n", get_page_size(size), sizeof(t_header));

	page_type = init_global(size);
	test = findPlace(&g_pages_array[page_type], size);

	return (test->mem);
}
