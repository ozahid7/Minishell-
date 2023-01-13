# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajafy <ajafy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/01 18:38:23 by ajafy             #+#    #+#              #
#    Updated: 2023/01/13 15:14:32 by ajafy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC = Parsing/minishell.c Parsing/delete_quotes.c Parsing/create_lst_temp.c Parsing/remplire_env.c \
		Parsing/expand.c Parsing/join_temp.c Parsing/delete_spaces.c Parsing/check_redirections.c \
		Parsing/check_redirections_utils.c Parsing/delete_node.c Parsing/remplire_list.c \
		Parsing/redirections_split.c Parsing/redirections_split_utils.c Parsing/redirections.c \
		Parsing/herdoc.c Parsing/signals_handler.c Parsing/free_listes.c

OBJ = $(addprefix build/, $(SRC:.c=.o))

CC = cc -g

NAME = minishell

CFLAGS = -Wall -Wextra -Werror 

LIBFT = Libft/libft.a 

LIBFT_DIR = Libft/

EXECUTE = ./minishell

INC = -I /Users/ajafy/.brew/opt/readline/include

HEADER = include/minishell.h

build/%.o : %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC) 

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@$(CC)  $(OBJ) -lreadline -L /Users/ajafy/.brew/opt/readline/lib -o \
	$(NAME) $(LIBFT)
	@echo "Minishell Maked"


$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) bonus -C $(LIBFT_DIR)
	@echo "Libft Maked"
	
clean :
	@rm -rf build
	@$(MAKE) clean -C $(LIBFT_DIR)
	@echo "Clean"

fclean : clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@rm -rf $(NAME)

re : fclean all