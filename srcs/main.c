/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:06:06 by amoinier          #+#    #+#             */
/*   Updated: 2017/11/22 19:52:36 by amoinier         ###   ########.fr       */
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
	printf("%lu\n", sizeof(short));
	printf("%lu\n", sizeof(int));
	printf("%lu --\n", sizeof(char));

	for (int i = 0; i < 150; i++)
	{
		text = malloc(40);
		text[0] = 'S';
		text[1] = 'A';
		text[2] = 'L';
		text[3] = 'U';
		printf("-----\n");
		printf("%s + %d\n", text, i);
	}

	return (0);
}
