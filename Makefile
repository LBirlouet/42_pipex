# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/22 10:57:44 by lbirloue          #+#    #+#              #
#    Updated: 2024/03/01 15:15:07 by lbirloue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	pipex

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror

INCLUDES		=	includes/pipex.h

INCLUDES_BONUS	=	includes_bonus/pipex_bonus.h


SRCS			=	srcs/main.c \
					srcs/get_path.c \
					srcs/childs.c \
					srcs/free_pipex.c \

FT_PRINTF		=	libftprintf.a

FT_PRINTF_PATH	=	ft_printf

LIBFT		=	libft.a

LIBFT_PATH	=	libft

OBJ_DIR			=	objects

OBJS			=	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

GREEN			=	\033[1;92m
RED				=	\033[1;91m
NC				=	\033[0m

${OBJ_DIR}/%.o : %.c 
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null 2>&1 

all : $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME) : $(OBJS) ${FT_PRINTF} ${LIBFT}
	@$(CC) $(OBJS) $(CFLAGS) -o ${NAME} ${FT_PRINTF} ${LIBFT} -g > /dev/null 2>&1 
	@printf "${GREEN}$(NAME) compiled${NC}\n" || (printf "${RED}$(NAME) error${NC}\n" && exit 1)

bonus : $(OBJS) ${FT_PRINTF} ${LIBFT}
	@$(CC) $(OBJS) $(CFLAGS) -o ${NAME} ${FT_PRINTF} ${LIBFT} > /dev/null 2>&1
	@printf "${GREEN}$(NAME) bonus compiled${NC}\n" || (printf "${RED}$(NAME) bonus error${NC}\n" && exit 1)

${FT_PRINTF}:
	@${MAKE} -C ${FT_PRINTF_PATH} > /dev/null 2>&1
	@mv ${FT_PRINTF_PATH}/${FT_PRINTF} .
	@printf "${GREEN}libft compiled${NC}\n" || (printf "${RED}libft error${NC}\n" && exit 1)

${LIBFT}:
	@${MAKE} -C ${LIBFT_PATH} > /dev/null 2>&1
	@mv ${LIBFT_PATH}/${LIBFT} .
	@printf "${GREEN}libftprintf compiled${NC}\n" || (printf "${RED}libftprintf error${NC}\n" && exit 1)

clean:
	@rm -rf $(OBJ_DIR)  > /dev/null 2>&1
	@${MAKE} clean -C ${FT_PRINTF_PATH} > /dev/null 2>&1
	@${MAKE} clean -C ${LIBFT_PATH} > /dev/null 2>&1
	@${RM} ${FT_PRINTF} > /dev/null 2>&1
	@${RM} ${LIBFT} > /dev/null 2>&1
	@printf "${RED}all cleaned${NC}\n"

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re