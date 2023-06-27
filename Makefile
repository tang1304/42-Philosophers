# --- VARIABLES --- #
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address
SRCS_DIR = ./srcs/
SRCS = 
OBJ_DIR = objs/
OBJ = ${SRCS:%.c=${OBJ_DIR}%.o}
NAME = philosophers
RM = rm -f
HEADER = ${SRCS_DIR}philosophers.h
LIBFT = libft/libft.a
LIBFT_DIR = libft/

# --- COLORS --- #

_NOC	:=	\033[0m
_RED	:=	\033[1;31m
_GREEN	:=	\033[1;32m

# --- RULES --- #

${NAME} :	${OBJ}
		${CC} ${CFLAGS} ${OBJ} ${LIBFT} -o ${NAME}
		@echo "${_GREEN}### ${NAME} created ###${_NOC}\n"

${OBJ}: ${OBJ_DIR}%.o :	${SRCS_DIR}%.c ${HEADER} ${LIBFT}
		@mkdir -p objs
		${CC} ${CFLAGS} -I/usr/include -c $< -o $@

${LIBFT}: FORCE
		${MAKE} -sC ${LIBFT_DIR}

FORCE:

all :	${NAME}

clean :
		@${MAKE} clean -sC ${LIBFT_DIR}
		rm -rf objs/
		@echo "${_RED}### Removed Philo object files ###${_NOC}"

fclean :	clean
		@${MAKE} fclean -sC ${LIBFT_DIR}
		${RM} ${NAME}
		@echo "${_RED}### Removed ${NAME} ###${_NOC}"

re : 	fclean all

.PHONY : all clean fclean re FORCE
