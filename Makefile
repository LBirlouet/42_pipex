# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/22 10:57:44 by lbirloue          #+#    #+#              #
#    Updated: 2024/03/01 11:22:56 by lbirloue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	pipex

CC				=	gcc

CFLAGS			=	-Wall -Wextra #-Werror

INCLUDES		=	includes/pipex.h

INCLUDES_BONUS	=	includes_bonus/pipex_bonus.h


SRCS			=	srcs/main.c \
					srcs/get_path.c \
					srcs/childs.c \
					srcs/utils/ft_split.c \
					srcs/utils/ft_substr.c \
					srcs/utils/ft_strjoin.c \
					srcs/utils/ft_strlen.c \
					srcs/utils/free_pipex.c \
					# srcs/utils/ft_lstadd_back.c \
					# srcs/utils/ft_lstclear.c \
					# srcs/utils/ft_lstdelone.c \
					# srcs/utils/ft_lstnew.c

FT_PRINTF		=	libftprintf.a

FT_PRINTF_PATH	=	ft_printf

OBJ_DIR			=	objects

OBJS			=	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

${OBJ_DIR}/%.o : %.c 
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all : $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME) : $(OBJS) ${FT_PRINTF}
	$(CC) $(OBJS) $(CFLAGS) -o ${NAME} ${FT_PRINTF}

bonus : $(OBJS) ${FT_PRINTF}
	$(CC) $(OBJS) $(CFLAGS) -o ${NAME} ${FT_PRINTF}

${FT_PRINTF}:
	${MAKE} -C ${FT_PRINTF_PATH} 
	mv ${FT_PRINTF_PATH}/${FT_PRINTF} .

clean:
	rm -rf $(OBJ_DIR) 
	${MAKE} clean -C ${FT_PRINTF_PATH} 
	${RM} ${FT_PRINTF} 

fclean: clean
	rm -rf $(NAME) 

re: fclean all

.PHONY: all clean fclean re