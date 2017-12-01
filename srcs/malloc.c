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
		if (!(g_pages_array[page_type].mem = alloc_mmap(get_page_size(size))) || g_pages_array[page_type].mem == MAP_FAILED)
			return (-1);
	}
	if (!g_pages_array[page_type].init)
	{
		g_pages_array[page_type].init = (t_header *)g_pages_array[page_type].mem;
		g_pages_array[page_type].init->size = 0;
		g_pages_array[page_type].init->page = &g_pages_array[page_type];
		g_pages_array[page_type].init->mem = ((void *)g_pages_array[page_type].init + sizeof(t_header));
		g_pages_array[page_type].init->space = get_page_size(size) - sizeof(t_header);
		g_pages_array[page_type].init->next = NULL;

		g_pages_array[page_type].max_space_size = g_pages_array[page_type].init->space;
	}

	return (page_type);
}

static t_header *findPlace(t_page *pages, size_t size)
{
	t_header	*tmp;

	if ((pages->max_space_size < (size + sizeof(t_header))))
	{
		if (!pages->next)
		{
			if (init_new_page(pages, size))
				return (findPlace(pages->next, size));
			else
				return (NULL);
		}
		else
			return (findPlace(pages->next, size));
	}
	else
	{
		if (pages->init)
		{
			tmp = pages->init;
			while (tmp)
			{
				if (tmp->size == 0 && size <= (tmp->size + tmp->space))
				{
					tmp->space = (tmp->space + tmp->size) - size;
					tmp->size = size;
					pages->max_space_size = tmp->space;
					return (tmp);
				}
				else if ((int)(tmp->space - (size + sizeof(t_header))) >= 0)
				{
					init_new_block(pages, tmp, size);
					return (tmp->next);
				}
				tmp = tmp->next;
			}
			return (NULL);
		}
		else
			return (NULL);
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
