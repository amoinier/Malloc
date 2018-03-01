# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/07 12:02:38 by amoinier          #+#    #+#              #
#    Updated: 2018/03/01 16:37:49 by amoinier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
PATHLIB = /libft_malloc_$(HOSTTYPE).so

LINK = libft_malloc.so

FLAGS =	-g -Wall -Werror -Wextra -fPIC

HEADERS = -I ./incs -I ./libft

LIBRARIES = -L./libft -lft

SRC_DIR =	./srcs/
FILENAMES = free.c malloc.c realloc.c show_alloc_mem.c alloc_mmap.c init_element.c page_info.c print_memory.c find_ptr.c find_before_page.c

OBJ_DIR = ./obj/
OBJ = $(FILENAMES:.c=.o)
OBJ_PATHS = $(addprefix $(OBJ_DIR),$(OBJ))

all: $(NAME)

$(NAME): $(OBJ_PATHS)
	@rm -f $(LINK)
	cd ./libft && make
	gcc $(OBJ_PATHS) $(HEADERS) $(LIBRARIES) -shared -o $(NAME)
	ln -s $(addprefix $(shell pwd), $(PATHLIB)) $(LINK)
	$(shell export LD_LIBRARY_PATH=./)

$(OBJ_PATHS): $(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	gcc $(FLAGS) $(HEADERS) -c $< -o $@

clean:
	rm -f $(OBJ_PATHS)
	cd ./libft && make fclean

fclean: clean
	rm -f $(NAME) $(LINK)

re: fclean all

.PHONY: all clean fclean re
