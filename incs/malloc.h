/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 11:59:20 by amoinier          #+#    #+#             */
/*   Updated: 2017/11/23 18:01:01 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		MALLOC_H
# define 	MALLOC_H

# include 	<stdlib.h>
# include 	<stdio.h>
# include	<sys/mman.h>
# include 	"libft.h"

# define 	BLOCK_NBR 	100

# define 	TINY 	(getpagesize() * 2) - sizeof(t_page)
# define 	SMALL 	(getpagesize() * 4) - sizeof(t_page)

# define 	TINY_SIZE 	(TINY - (sizeof(t_header) * BLOCK_NBR)) / BLOCK_NBR
# define 	SMALL_SIZE 	(SMALL - (sizeof(t_header) * BLOCK_NBR)) / BLOCK_NBR

typedef struct 		s_header {
	char 			free;
	unsigned int	size;
	unsigned int	space;
	void 			*mem;
	struct s_header	*next;
} 					t_header;


typedef struct 		s_page {
	unsigned int 	max_space_size;
	void 			*mem;
	struct s_page	*next;
	t_header		*init;
} 					t_page;

void 				free(void *ptr);
void 				*malloc(size_t size);
void 				*realloc(void *ptr, size_t size);

void 				init_new_block(t_page *pages, t_header *header, size_t size);
void 				*init_new_page(t_page *pages, size_t size);

void 				*alloc_mmap(size_t size);

unsigned int		get_page_size(size_t size);
int					get_page_type(size_t size);


#endif
