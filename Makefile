# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/07 12:02:38 by amoinier          #+#    #+#              #
#    Updated: 2017/11/22 15:26:12 by amoinier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME =			libft_malloc_$(HOSTTYPE).so

PATHLIB = 		/libft_malloc_$(HOSTTYPE).so

LINK =			libft_malloc.so

CC =			gcc

FLAGS =			-Wall -Werror -Wextra -fPIC

HEADERS =		-I ./incs -I $(LIBFT_DIR)

LIBRARIES =		-L$(LIBFT_DIR) -lft

LIBFT =			$(LIBFT_DIR)libft.a

LIBFT_DIR =		./libft/

SRC_DIR =		./srcs/

OBJ_DIR_NAME =	obj
OBJ_DIR =		./obj/

FILENAMES =		free malloc realloc show_alloc_mem alloc_mmap init_element page_info print_memory

OBJ_PATHS :=	$(addsuffix .o,$(FILENAMES))
OBJ_PATHS :=	$(addprefix $(OBJ_DIR),$(OBJ_PATHS))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_PATHS)
	$(CC) $(OBJ_PATHS) $(HEADERS) $(LIBRARIES) -shared -o $(NAME)
	@rm -f $(LINK)
	ln -s $(addprefix $(shell pwd), $(PATHLIB)) $(LINK)
	$(shell export LD_LIBRARY_PATH=./)

$(OBJ_PATHS): $(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $(FLAGS) $(HEADERS) $< -o $@

$(LIBFT):
	(cd $(LIBFT_DIR) && make)

clean:
	rm -f $(OBJ_PATHS)
	(cd $(LIBFT_DIR) && make fclean)
	find . -name "$(OBJ_DIR_NAME)" -maxdepth 1 -type d -empty -delete

fclean: clean
	rm -f $(NAME) $(LINK)

re: fclean all

.PHONY: all $(NAME) $(OBJ_PATHS) $(LIBFT) clean fclean re
