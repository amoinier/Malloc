/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 17:17:21 by amoinier          #+#    #+#             */
/*   Updated: 2017/11/23 19:07:31 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t	get_page_size(size_t size)
{
	size_t i;

	if (size <= TINY_SIZE)
		return ((int)TINY);
	else if (size <= SMALL_SIZE)
		return ((int)SMALL);
	else
	{
		i = ((size + sizeof(t_page) + sizeof(t_header)) / (getpagesize())) + 1;
		return (getpagesize() * i);
	}
}

int		get_page_type(size_t size)
{
	if (size <= TINY_SIZE)
		return (0);
	else if (size <= SMALL_SIZE)
		return (1);
	else
		return (2);
}
