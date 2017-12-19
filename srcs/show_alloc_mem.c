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

#include "malloc.h"

extern t_page g_pages_array[3];

void				show_alloc_mem(void)
{
	int				i;
	unsigned int	total;
	char			*page_name[3];

	page_name[0] = "TINY : ";
	page_name[1] = "SMALL : ";
	page_name[2] = "LARGE : ";
	total = 0;
	i = 0;
	while (i < 3)
	{
		total = first_loop(page_name, total, i);
		i++;
	}
	print_total(total);
	return ;
}

static unsigned int	first_loop(char *page_nam[3], unsigned int total, int i)
{
	t_page			*tmp_page;
	int				j;

	ft_putstr(page_nam[i]);
	print_memory((void *)page_nam[i]);
	ft_putchar('\n');
	tmp_page = &g_pages_array[i];
	j = 0;
	while (tmp_page)
	{
		total = second_loop(tmp_page, total, j);
		tmp_page = tmp_page->next;
		j++;
	}
	return (total);
}

static unsigned int	second_loop(t_page *tmp_page, unsigned int total, int j)
{
	t_header		*tmp_header;

	tmp_header = tmp_page->init;
	ft_putstr("PAGE ");
	ft_putnbr(j);
	ft_putchar('\n');
	while (tmp_header)
	{
		print_header(tmp_header);
		total += tmp_header->size;
		tmp_header = tmp_header->next;
	}
	return (total);
}

static void			print_header(t_header *tmp_header)
{
	print_memory(tmp_header->mem);
	ft_putstr(" - ");
	print_memory(tmp_header->mem + tmp_header->size);
	ft_putstr(" : ");
	ft_putnbr(tmp_header->size);
	ft_putstr(" octets\n");
	return ;
}

static void			print_total(unsigned total)
{
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr(" octets\n");
	return ;
}
