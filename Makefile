# --- VARIABLES --- #
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread -O2 -g3 -fsanitize=thread #-fsanitize=address
SRCS_DIR = ./SRCS/
SRCS = actions.c errors.c exec.c init.c lib.c main.c utils.c
OBJ_DIR = objs/
OBJ = ${SRCS:%.c=${OBJ_DIR}%.o}
NAME = philo
RM = rm -f
HEADER = philosophers.h

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
		rm -rf objs/
		@echo "${_RED}### Removed Philo object files ###${_NOC}"

fclean :	clean
		${RM} ${NAME}
		@echo "${_RED}### Removed ${NAME} ###${_NOC}"

re : 	fclean all

.PHONY : all clean fclean re FORCE
