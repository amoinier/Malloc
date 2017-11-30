/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:07:41 by amoinier          #+#    #+#             */
/*   Updated: 2017/11/22 15:22:54 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include 	"malloc.h"

extern 		t_page 	g_pages_array[3];

void 		show_alloc_mem()
{
	int 			i;
	int 			j;
	unsigned int 	total;
	char			*page_name[3];
	t_page 			*tmp_page;
	t_header 		*tmp_header;

	page_name[0] = "TINY : ";
	page_name[1] = "SMALL : ";
	page_name[2] = "LARGE : ";
	total = 0;
	i = 0;
	while (i < 3)
	{
		ft_putstr(page_name[i]);
		print_memory((void *)page_name[i]);
		ft_putchar('\n');
		tmp_page = &g_pages_array[i];
		j = 0;
		while (tmp_page)
		{
			tmp_header = tmp_page->init;
			ft_putstr("PAGE ");
			ft_putnbr(j);
			ft_putchar('\n');
			while (tmp_header)
			{
				print_memory(tmp_header->mem);
				ft_putstr(" - ");
				print_memory(tmp_header->mem + tmp_header->size);
				ft_putstr(" : ");
				ft_putnbr(tmp_header->size);
				ft_putstr(" octets\n");
				total += tmp_header->size;
				tmp_header = tmp_header->next;
			}
			tmp_page = tmp_page->next;
			j++;
		}
		i++;
	}
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr(" octets\n");
}
