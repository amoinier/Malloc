/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 11:59:20 by amoinier          #+#    #+#             */
/*   Updated: 2018/03/02 15:21:03 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <stdio.h>
# include <sys/mman.h>
# include "libft.h"

# define BLOCK_NBR 	100

# define TINY 	(getpagesize() * 15) - sizeof(t_page)
# define SMALL 	(getpagesize() * 30) - sizeof(t_page)

# define TINY_SIZE 	(TINY - (sizeof(t_header) * BLOCK_NBR)) / BLOCK_NBR
# define SMALL_SIZE 	(SMALL - (sizeof(t_header) * BLOCK_NBR)) / BLOCK_NBR

typedef struct		s_header {
	size_t			size;
	size_t			space;
	void			*mem;
	struct s_page	*page;
	struct s_header	*next;
}					t_header;

typedef struct		s_page {
	size_t			max_space_size;
	void			*mem;
	struct s_page	*next;
	t_header		*init;
}					t_page;

void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				show_alloc_mem();
t_header			*find_place(t_page *pages, size_t size);
void				init_new_block(t_page *page, t_header *header, size_t size);
void				*init_new_page(t_page *pages, size_t size);
void				*alloc_mmap(size_t size);
size_t				get_page_size(size_t size);
int					get_page_type(size_t size);
void				print_memory(const void *addr);
t_header			*find_ptr(void *ptr);
t_page				*find_before_page(t_page *page);

#endif
