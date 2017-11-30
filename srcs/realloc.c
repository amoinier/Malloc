/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:08:10 by amoinier          #+#    #+#             */
/*   Updated: 2017/11/22 15:23:06 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void 		*realloc(void *ptr, size_t size)
{
	t_header *header;

	header = (t_header *)(ptr - sizeof(t_header));
	return NULL;
}
