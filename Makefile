# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/31 18:49:40 by vgroux            #+#    #+#              #
#    Updated: 2023/03/09 12:00:18 by jolivier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


GREENGREEN = \033[38;5;46m
RED = \033[0;31m
GREY = \033[38;5;240m
RESET = \033[0m

NAME =     minishell

CC =         gcc
CFLAGS =     -Wall -Wextra -Werror -g
RM =         rm -rf

DIR_H = headers/
DIR_S =	srcs/
CREATE_DIR_O = @mkdir -p objs
DIR_O =	objs/

SRCS_LIST =	main.c lexer.c expander.c parser.c redirect.c exec.c free.c \
			parsing/parsing.c parsing/parsing_var.c 

SRCS =		${addprefix ${DIR_S}, ${SRCS_LIST}}

OBJS =		${SRCS:${DIR_S}%.c=${DIR_O}%.o}

# Compile la Libft
DIR_LIBFT = libft/
LIBFT_INC = -I ${DIR_LIBFT}
LIBFT =	${DIR_LIBFT}libft.a
FT_LNK = -L ${DIR_LIBFT} -l ft

LIBS = ${FT_LNK}

# ${NAME}: title ${LIBFT} ${MLX} ${OBJS}
${NAME}: ${LIBFT} ${OBJS}
	@echo "$(RESET)[$(GREENGREEN)${NAME}$(RESET)]: Minishell Objects were created${GREY}"
	${CC} ${OBJS} ${LIBS} -lreadline -o ${NAME}
	@echo "$(RESET)[$(GREENGREEN)${NAME}$(RESET)]: Minishell created !"

title:
	@echo "$(GREENGREEN) ██████╗██████╗  █████╗  ██████╗████████╗    ██████╗ ██╗$(RESET)"
	@echo "$(GREENGREEN) ██╔════╝██╔══██╗██╔══██╗██╔════╝╚══██╔══╝   ██╔═══██╗██║$(RESET)"
	@echo "$(GREENGREEN) █████╗  ██████╔╝███████║██║        ██║█████╗██║   ██║██║$(RESET)"
	@echo "$(GREENGREEN) ██╔══╝  ██╔══██╗██╔══██║██║        ██║╚════╝██║   ██║██║$(RESET)"
	@echo "$(GREENGREEN) ██║     ██║  ██║██║  ██║╚██████╗   ██║      ╚██████╔╝███████╗$(RESET)"
	@echo "$(GREENGREEN) ╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝   ╚═╝       ╚═════╝ ╚══════╝$(RESET)"

${LIBFT}:
	@echo "[$(GREENGREEN)${NAME}$(RESET)]: Creating Libft...${GREY}"
	${MAKE} -sC ${@D}
	@echo "$(RESET)[$(GREENGREEN)${NAME}$(RESET)]: Libft Objects were created"

all: ${NAME}

${DIR_O}%.o:${DIR_S}%.c
	@printf "\033[38;5;240m"
	@mkdir -p ${DIR_O}
	@mkdir -p ${DIR_O}parsing
	${CC} ${CFLAGS} ${LIBFT_INC} -I ${DIR_H} -o $@ -c $<

clean:
	@echo "$(RED) ██████╗██╗     ███████╗ █████╗ ███╗   ██╗██╗███╗   ██╗ ██████╗$(RESET)"
	@echo "$(RED) ██╔════╝██║     ██╔════╝██╔══██╗████╗  ██║██║████╗  ██║██╔════╝$(RESET)"
	@echo "$(RED) ██║     ██║     █████╗  ███████║██╔██╗ ██║██║██╔██╗ ██║██║  ███╗$(RESET)"
	@echo "$(RED) ██║     ██║     ██╔══╝  ██╔══██║██║╚██╗██║██║██║╚██╗██║██║   ██║$(RESET)"
	@echo "$(RED) ╚██████╗███████╗███████╗██║  ██║██║ ╚████║██║██║ ╚████║╚██████╔╝$(RESET)"
	@echo "$(RED)  ╚═════╝╚══════╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═══╝ ╚═════╝ $(RESET)"
	@echo "[$(RED)${NAME}$(RESET)]: Cleaning Minishell Objects...${GREY}"
	${RM} ${OBJS}
	${RM} ${DIR_O}
	@echo "[$(RED)${NAME}$(RESET)]: Minishell Objects were cleaned${GREY}"

libclean:
	@echo "${RESET}[$(RED)${NAME}$(RESET)]: Cleaning Libft...${GREY}"
	${MAKE} -sC ${DIR_LIBFT} fclean
	@echo "${RESET}[$(RED)${NAME}$(RESET)]: Libft Objects were cleaned"

fclean: clean libclean
	@echo "${RESET}[$(RED)${NAME}$(RESET)]: Cleaning Minishell...${GREY}"
	${RM} ${NAME}
	@echo "${RESET}[$(RED)${NAME}$(RESET)]: Minishell Executable was cleaned"

re: fclean all

.PHONY: all clean fclean re title libclean 