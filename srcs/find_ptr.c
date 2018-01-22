/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ptr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 16:43:22 by amoinier          #+#    #+#             */
/*   Updated: 2018/01/22 18:50:37 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_page g_pages_array[3];

static t_header		*find_block(t_page *page, void *ptr)
{
	t_header	*tmp;
	t_header	*head;

	head = NULL;
	tmp = page->init;
	while (tmp && !head)
	{
		if (tmp->mem == ptr)
			head = (t_header *)(ptr - sizeof(t_header));
		tmp = tmp->next;
	}
	return (head);
}

static t_header		*find_page(t_page *page, void *ptr)
{
	t_page		*tmp;
	t_header	*head;

	head = NULL;
	tmp = page;
	while (tmp && !head)
	{
		head = find_block(tmp, ptr);
		tmp = tmp->next;
	}
	return (head);
}

t_header			*find_ptr(void *ptr)
{
	int			i;
	t_header	*head;

	head = NULL;
	i = 0;
	while (i < 3 && !head)
	{
		head = find_page(&g_pages_array[i], ptr);
		i++;
	}
	return (head);
}
