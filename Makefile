GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -Iinclude
#-g3 -fsanitize=thread

SRCS = src/main.c src/parse_input.c src/init_symposium.c src/start_symposium.c \
	   src/philo_action.c src/clean_up.c src/utils.c src/clean_up_utils.c src/start_symposium_utils.c \
	   

OBJS = $(SRCS:src/%.c=obj/%.o)

NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)[OK] Binary $(NAME) created$(RESET)"

obj/%.o: src/%.c | obj
	@$(CC) $(CFLAGS) -c $< -o $@

obj:
	@mkdir -p obj
	
clean:
	@rm -rf obj
	@echo "$(RED)[CLEAN] Removed object files$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)[CLEAN] Removed binary$(RESET)"

re: fclean all

.PHONY: all clean fclean re
