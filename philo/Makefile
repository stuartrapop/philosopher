NAME = philo

# SRCS_PATH_GNL = ./gnl
SRCS_PATH_MAIN = ./main

OBJS_PATH = ./

SRCS_NAME_MAIN = philosopher_1.c \
					philosopher_2.c \
					philosopher_3.c \
					utils.c \
					string.c

# SRCS_NAME_GNL = gnl.c \
# 			gnl_utils.c


SRCS = $(addprefix $(SRCS_PATH_MAIN)/,$(SRCS_NAME_MAIN))
# SRCS += $(addprefix $(SRCS_PATH_GNL)/,$(SRCS_NAME_GNL))


HEADER_DIR = ./headers

# FLAG = -Wall -Wextra -Werror -I$(HEADER_DIR) -g3 -fsanitize=thread
FLAG = -Wall -Wextra -Werror -I$(HEADER_DIR) -g3 -fsanitize=address
# FLAG = -Wall -Wextra -Werror -I$(HEADER_DIR) -g3 -fsanitize=undefined
# FLAG = -Wall -Wextra -Werror -I$(HEADER_DIR)

CC = GCC $(FLAG)

OBJS = ${SRCS:.c=.o}

%.o:%.c
	$(CC) -o $@ -c $<

${NAME} : ${OBJS}
	$(CC)    $(OBJS) -o ${NAME}

all : ${NAME}
	@echo "$(COLOUR_RED)Make ${NAME} completed$(COLOUR_END)"

clean :
	rm -f ${OBJS} $(OBJS_BONUS)
	@echo "$(COLOUR_GREEN)Make Clean Executed$(COLOUR_END)"

fclean : clean
	rm -f ${NAME}
	@echo "$(COLOUR_RED)Executable ${NAME} removed $(COLOUR_END)"

re : fclean all



.PHONY : all clean fclean re

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m