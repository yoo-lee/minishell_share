
SRC_DIR := ./srcs
SRC :=  set_env+.c \
	   

OBJ_DIR := ./.objects
OBJS := $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

DEPS := $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.d))

INCLUDE := -I./includes -I$(shell brew --prefix readline)/include
LDFLAGS := libft/libft.a -L$(shell brew --prefix readline)/lib -lreadline -lhistory

NAME := minishell

CC := gcc
CFLAGS := -g -Wall -Wextra -Werror -MMD -MP

LIBFT := libft

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@-mkdir -p $(OBJ_DIR) $(DEP_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	@make clean -C $(LIBFT)
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	$(RM) libft/libft.a
	$(RM) $(NAME)

re: fclean all

test: all
	@bash test.sh 2> /dev/null

debug: CFLAGS += -fsanitize=address
debug: LDFLAGS += -fsanitize=address
debug: re

dot: all
	@dot -Tsvg ast.dot > ast.svg

-include $(DEPS)

.PHONY: all clean fclean re test dot
	