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
	int 		i;
	int 		j;
	char		*page_name[3];
	t_page 		*tmp_page;
	t_header 	*tmp_header;

	page_name[0] = "TINY\n";
	page_name[1] = "SMALL\n";
	page_name[2] = "LARGE\n";
	i = 0;
	while (i < 3)
	{
		ft_putstr(page_name[i]);
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
				print_memory(tmp_header->mem, tmp_header->size);
				tmp_header = tmp_header->next;
			}
			ft_putstr("XXX\n");
			tmp_page = tmp_page->next;
			j++;
		}
		i++;
	}
}
