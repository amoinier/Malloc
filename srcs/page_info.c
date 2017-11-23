/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 17:17:21 by amoinier          #+#    #+#             */
/*   Updated: 2017/11/23 14:28:55 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

unsigned int 	get_page_size(size_t size)
{
	if (size <= TINY_SIZE)
		return ((int)TINY);
	else if (size <= SMALL_SIZE)
		return ((int)SMALL);
	else
		return ((int)size);
}

unsigned int 	get_block_size(size_t size)
{
	if (size <= TINY_SIZE)
		return ((int)TINY_SIZE);
	else if (size <= SMALL_SIZE)
		return ((int)SMALL_SIZE);
	else
		return ((int)size);
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
