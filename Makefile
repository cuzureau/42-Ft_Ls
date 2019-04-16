# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/11 20:55:49 by cuzureau          #+#    #+#              #
#    Updated: 2017/10/29 21:13:23 by cuzureau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

C_FLAGS = -Wall -Wextra -Werror -g

OBJ_PATH = ./obj/
LFT_PATH = ./libft/
SRC_PATH = ./src/

OBJ_NAME = $(SRC_NAME:.c=.o)
INC_NAME = ft_ls.h
SRC_NAME = main.c infos.c print.c tree.c check.c padding.c tools.c

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = -I ./include -I ./libft/include/

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LFT_PATH)
	gcc -o $(NAME) -L $(LFT_PATH) -lft $^ -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(OBJ_PATH) 2> /dev/null || true
	gcc $(C_FLAGS) $(INC) -o $@ -c $<

clean:
	make -C $(LFT_PATH) clean
	rm -rf $(OBJ_PATH)

fclean: clean
	make -C $(LFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
