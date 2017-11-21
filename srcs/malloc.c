/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:06:54 by amoinier          #+#    #+#             */
/*   Updated: 2017/11/21 19:26:19 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_page 	g_pages_array[3] = {
	{'0', NULL, NULL, NULL},
	{'1', NULL, NULL, NULL},
	{'1', NULL, NULL, NULL}
};

static void *alloc_mmap(size_t size)
{
	void 	*tmp;

	tmp = (void *)mmap(NULL, size,  PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0);
	printf("My_Malloc\n");
	return tmp;
}

static size_t 	getPageSize(size_t size)
{
	if (size <= TINY_SIZE)
		return (TINY);
	else if (size <= SMALL_SIZE)
		return (SMALL);
	else
		return (size);
}

static int		getPageType(size_t size)
{
	if (size <= TINY_SIZE)
		return (0);
	else if (size <= SMALL_SIZE)
		return (1);
	else
		return (2);
}

static int 		init_global(size_t size)
{
	int 	page_type;

	page_type = getPageType(size);
	if (!g_pages_array[page_type].mem)
	{
		if (!(g_pages_array[page_type].mem = alloc_mmap(sizeof(getPageSize(size)))))
			return (-1);
	}
	if (!g_pages_array[page_type].init)
	{
		g_pages_array[page_type].init = g_pages_array[page_type].mem;
		g_pages_array[page_type].init->free = '1';
		g_pages_array[page_type].init->mem = g_pages_array[page_type].init + sizeof(*g_pages_array[page_type].init);
		g_pages_array[page_type].init->next = NULL;
	}

	return (page_type);
}

static void 	findPlace(t_page pages, size_t size)
{
	if (g_pages_array[getPageType(size)].space_left == '0')
	{
		if (!(g_pages_array[getPageType(size)].next = (t_page *)alloc_mmap(sizeof(getPageType(size)))))
			return ;
		else
		{
			g_pages_array[getPageType(size)].next->space_left = '1';
			g_pages_array[getPageType(size)].next->mem = g_pages_array[getPageType(size)].next + sizeof(*g_pages_array[getPageType(size)].next) + 1;
			g_pages_array[getPageType(size)].next->next = NULL;

			g_pages_array[getPageSize(size)].next->init = g_pages_array[getPageType(size)].next->mem + sizeof(g_pages_array[getPageSize(size)].next->init) + 1;
			g_pages_array[getPageType(size)].next->init->free = '1';
			g_pages_array[getPageType(size)].next->init->mem = g_pages_array[getPageType(size)].init + sizeof(*g_pages_array[getPageType(size)].init) + 1;
			g_pages_array[getPageType(size)].next->init->next = NULL;
		}
	}
	else {

	}
}

void 		*malloc(size_t size)
{
	int 	page_type;

	page_type = init_global(size);

	printf("%c\n", g_pages_array[page_type].next->mem);

	return (NULL);
}
