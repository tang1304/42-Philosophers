# --- VARIABLES --- #
CC = cc
CFLAGS = -Wall -Wextra -Werror - pthread -g3 #-fsanitize=address
SRCS_DIR = ./srcs/
SRCS = main.c init.c errors.c \
		ft_atoi.c ft_bzero.c
OBJ_DIR = objs/
OBJ = ${SRCS:%.c=${OBJ_DIR}%.o}
NAME = philosophers
RM = rm -f
HEADER = ${SRCS_DIR}philosophers.h

# --- COLORS --- #

_NOC	:=	\033[0m
_RED	:=	\033[1;31m
_GREEN	:=	\033[1;32m

# --- RULES --- #

${NAME} :	${OBJ}
		${CC} ${CFLAGS} ${OBJ} -o ${NAME}
		@echo "${_GREEN}### ${NAME} created ###${_NOC}\n"

${OBJ}: ${OBJ_DIR}%.o :	${SRCS_DIR}%.c ${HEADER}
		@mkdir -p objs
		${CC} ${CFLAGS} -I/usr/include -c $< -o $@

FORCE:

all :	${NAME}

clean :
		@${MAKE} clean -sC
		rm -rf objs/
		@echo "${_RED}### Removed Philo object files ###${_NOC}"

fclean :	clean
		@${MAKE} fclean -sC
		${RM} ${NAME}
		@echo "${_RED}### Removed ${NAME} ###${_NOC}"

re : 	fclean all

.PHONY : all clean fclean re FORCE
