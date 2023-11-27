NAME := philo

CC := gcc

#CFLAGS := -Wall -Wextra -Werror -g
CFLAGS := $(CFLAGS) -fsanitize=address -g
#CFLAGS := $(CFLAGS) -fsanitize=thread

SRC := main.c philo.c time.c free.c prot_print.c\
	   libft_func/ft_atoi.c libft_func/ft_calloc.c

SRC_DIR := src
OBJ_DIR := obj

INCLUDES := -I includes

OBJ := $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/libft_func
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@echo "Compiling $<"

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
