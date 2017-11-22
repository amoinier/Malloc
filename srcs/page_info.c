/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 17:17:21 by amoinier          #+#    #+#             */
/*   Updated: 2017/11/22 17:18:58 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t 	get_page_size(size_t size)
{
	if (size <= TINY_SIZE)
		return (TINY);
	else if (size <= SMALL_SIZE)
		return (SMALL);
	else
		return (size);
}

size_t 	get_block_size(size_t size)
{
	if (size <= TINY_SIZE)
		return (TINY_SIZE);
	else if (size <= SMALL_SIZE)
		return (SMALL_SIZE);
	else
		return (size);
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
