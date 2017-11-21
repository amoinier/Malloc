/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 11:59:20 by amoinier          #+#    #+#             */
/*   Updated: 2017/11/21 19:02:44 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		MALLOC_H
# define 	MALLOC_H

# include 	<stdlib.h>
# include	<sys/mman.h>
# include 	"libft.h"

# define 	TINY 	(getpagesize() * 2) - sizeof(t_page)
# define 	SMALL 	(getpagesize() * 4) - sizeof(t_page)

# define 	TINY_SIZE 	(TINY - (sizeof(t_header) * 100)) / 100
# define 	SMALL_SIZE 	(SMALL - (sizeof(t_header) * 100)) / 100

typedef struct 		s_header {
	char 			free;
	void 			*mem;
	struct s_header	*next;
} 					t_header;


typedef struct 		s_page {
	char 			space_left;
	void 			*mem;
	struct s_page	*next;
	t_header		*init;
} 					t_page;

void 				free(void *ptr);
void 				*malloc(size_t size);
void 				*realloc(void *ptr, size_t size);

#endif
