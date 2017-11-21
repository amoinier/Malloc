/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:06:06 by amoinier          #+#    #+#             */
/*   Updated: 2017/11/21 19:05:13 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int 		main(void)
{

	printf("%lu\n", TINY);
	printf("%lu\n", SMALL);
	printf("%lu\n", TINY_SIZE);
	printf("%lu\n", SMALL_SIZE);
	printf("%lu\n", sizeof(t_page));
	printf("%lu\n", sizeof(t_header));

	malloc(5);
	return (0);
}
