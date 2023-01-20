# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ozahid- <ozahid-@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/01 18:38:23 by ajafy             #+#    #+#              #
#    Updated: 2023/01/20 15:35:17 by ozahid-          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC = 	minishell.c Parsing/delete_quotes.c Parsing/create_lst_temp.c Parsing/remplire_env.c \
		Parsing/expand.c Parsing/join_temp.c Parsing/delete_spaces.c Parsing/check_redirections.c \
		Parsing/check_redirections_utils.c Parsing/delete_node.c Parsing/remplire_list.c \
		Parsing/redirections_split.c Parsing/redirections_split_utils.c Parsing/redirections.c \
		Parsing/herdoc.c Parsing/signals_handler.c Parsing/free_listes.c Parsing/minishell_utils.c\
		execution/red.c builtins/cd.c builtins/pwd_env_echo.c builtins/isbuiltins.c builtins/export1.c\
		builtins/export2.c builtins/export3.c builtins/ft_run.c builtins/unset.c builtins/temp.c\
		execution/execve.c execution/pipe.c printf_/ft_printf.c printf_/ft_putchar.c \
		printf_/ft_putstr.c printf_/ft_putnbr.c printf_/ft_argp.c printf_/ft_hexa.c printf_/ft_unsignednumber.c
		
OBJ = $(addprefix build/, $(SRC:.c=.o))

CC = cc

NAME = minishell

CFLAGS = -Wall -Wextra -Werror

LIBFT = Libft/libft.a 

LIBFT_DIR = Libft/

INC = -I /Users/$(USER)/.brew/opt/readline/include

HEADER = minishell.h

build/%.o : %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC) 

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@$(CC) $(OBJ) -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -o \
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