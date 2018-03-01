/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_before_page.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 16:43:22 by amoinier          #+#    #+#             */
/*   Updated: 2018/03/01 16:52:54 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_page g_pages_array[3];

static t_page		*find_page(t_page *page, t_page *find)
{
	t_page			*tmp;

	tmp = page;
	while (tmp && tmp->next != find)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

t_page				*find_before_page(t_page *page)
{
	int				i;
	t_page			*tmp;

	i = 0;
	tmp = NULL;
	while (i < 3 && !tmp)
	{
		tmp = find_page(&g_pages_array[i], page);
		i++;
	}
	return (tmp);
}
