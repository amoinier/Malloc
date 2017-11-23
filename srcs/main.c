/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:06:06 by amoinier          #+#    #+#             */
/*   Updated: 2017/11/23 19:13:18 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int 		main(void)
{
	char *text;

	printf("%lu\n", TINY);
	printf("%lu\n", SMALL);
	printf("%lu\n", TINY_SIZE);
	printf("%lu\n", SMALL_SIZE);
	printf("%d\n", getpagesize() * 2);
	printf("%lu --\n", sizeof(t_header));
	printf("%lu --\n", sizeof(t_page));

	for (int i = 0; i < 1; i++)
	{
		if (!(text = malloc(4000000000)))
			return (0);
		text[0] = 'S';
		text[1] = 'A';
		text[2] = 'L';
		text[3] = 'U';
		printf("%s + %d\n", text, (i + 1));
		printf("-----\n");
	}

	return (0);
}
