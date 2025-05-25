GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDEDIR = include

SRCDIR = .
SRCS = $(SRCDIR)/

OBJS = $(SRCS:.c=.o)


TARGET = philo

all:	$(TARGET)

$(TARGET):	$(OBJS) $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) -o  $(TARGET)
	@echo "$(TARGET): $(GREEN)object files were created$(RESET)"
	@echo "$(TARGET): $(GREEN)$(TARGET) was created$(RESET)"

%.o:	%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	@echo "$(RED)Cleaned object files$(RESET)"

fclean: clean
	rm -f $(TARGET)
	@echo "$(RED)Cleaned targets$(RESET)"

re:	fclean all
	@echo "$(GREEN)Rebuilding Library$(RESET)"