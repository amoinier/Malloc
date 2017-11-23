/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:06:54 by amoinier          #+#    #+#             */
/*   Updated: 2017/11/23 19:11:31 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_page 	g_pages_array[3] = {
	{0, NULL, NULL, NULL},
	{0, NULL, NULL, NULL},
	{0, NULL, NULL, NULL}
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
		printf("CREATE - Init - %d\n", get_page_size(size));
		g_pages_array[page_type].init = g_pages_array[page_type].mem;
		g_pages_array[page_type].init->free = '1';
		g_pages_array[page_type].init->size = 0;
		g_pages_array[page_type].init->mem = (void *)g_pages_array[page_type].init + sizeof(t_header);
		g_pages_array[page_type].init->space = get_page_size(size) - sizeof(t_header);
		g_pages_array[page_type].init->next = NULL;

		g_pages_array[page_type].max_space_size = g_pages_array[page_type].init->space;
		printf("CREATE - Init - Free Space = %d\n", g_pages_array[page_type].init->space);
	}

	return (page_type);
}

static t_header *findPlace(t_page *pages, size_t size)
{
	t_header	*tmp;

	printf("--- PAGES MAX SIZE = %d, result = %d ---\n", pages->max_space_size, (int)(pages->max_space_size - (size + sizeof(t_header))));
	if ((int)(pages->max_space_size - (size + sizeof(t_header))) < 0)
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
			printf("FINDPLACE - Start While\n");
			ft_putstr("1\n");
			tmp = pages->init;
			printf("!! CHECK VALUE !! -\nget_page_size() = %d\nsize = %zu\npages->max_space_size = %d\n- !! CHECK VALUE !!",
			get_page_size(size), size, pages->max_space_size);
			while (tmp)
			{
				ft_putstr("2\n");
				printf("!! CHECK VALUE !! tmp->free = %d tmp->space = %d tmp->size = %d !! CHECK VALUE !!\n", tmp->free, tmp->space, tmp->size);
				if (tmp->free == '1' && size <= (tmp->size + tmp->space))
				{
					ft_putstr("3\n");
					printf("FINDPLACE - Space and free block\n");
					tmp->free = '0';
					tmp->space = (tmp->space + tmp->size) - size;
					tmp->size = size;
					pages->max_space_size = tmp->space;
					printf("Space left - %d\n", tmp->space);
					return (tmp);
				}
				else if ((int)(tmp->space - (size + sizeof(t_header))) >= 0)
				{
					ft_putstr("4\n");
					init_new_block(pages, tmp, size);
					return (tmp->next);
				}
				tmp = tmp->next;
			}
			ft_putstr("5\n");
			return (NULL);
		}
		else
		{
			ft_putstr("6\n");
			return (NULL);
		}
	}
}

void 		*malloc(size_t size)
{
	int 	page_type;
	t_header	*test;

	page_type = init_global(size);
	if (page_type == -1)
		return (NULL);
	test = findPlace(&g_pages_array[page_type], size);

	return ((test ? test->mem : test));
}
