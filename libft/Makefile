# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajafy <ajafy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/20 11:21:12 by ajafy             #+#    #+#              #
#    Updated: 2023/01/20 11:29:25 by ajafy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC = ft_isalpha.c ft_memchr.c ft_strchr.c ft_strlen.c ft_tolower.c ft_atoi.c ft_isascii.c ft_memcmp.c ft_strdup.c ft_strncmp.c ft_toupper.c ft_bzero.c ft_isdigit.c ft_memcpy.c \
      ft_strlcat.c ft_strnstr.c ft_isalnum.c ft_isprint.c ft_memset.c ft_strlcpy.c ft_strrchr.c ft_memmove.c ft_calloc.c ft_substr.c ft_strjoin.c ft_putchar_fd.c ft_putstr_fd.c \
      ft_putnbr_fd.c ft_strtrim.c ft_putendl_fd.c ft_striteri.c ft_strmapi.c ft_split.c ft_split_utils.c ft_itoa.c

OBJ = $(addprefix build/, ${SRC:.c=.o})

SRCB = ft_lstnew.c  ft_lstsize.c ft_lstadd_back.c ft_lstlast.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c

OBJB = $(addprefix build/, ${SRCB:.c=.o})

CC = cc

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror

HEADER = libft.h

build/%.o : %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	@ar -rc $(NAME) $(OBJ)

clean :
	@rm -rf build

fclean : clean
	@rm -f $(NAME)

re : fclean all

bonus : all $(OBJB)
	@ar -rc $(NAME) $(OBJB)
