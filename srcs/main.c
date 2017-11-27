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

	for (int i = 0; i < 201; i++)
	{
		if (!(text = mallocs(40))) {
			ft_putstr("FUCK YOU\n");
			return (0);
		}
		text[0] = 'S';
		text[1] = 'A';
		text[2] = 'L';
		text[3] = 'U';
		text[4] = 'T';
		text[5] = 48 + (i % 9);
		text[6] = '\0';
		printf("%s + %d\n", text, (i + 1));
		// if (i % 2 == 0)
		// 	free(text);
		printf("-----\n");
	}

	show_alloc_mem();

	return (0);
}
