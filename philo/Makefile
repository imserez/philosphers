CFLAGS		:= -Wall -Werror -Wextra -MMD -pthread
CC			:= cc
NAME		:= philo
BUILD_DIR	:= build
SRCS		:= ft_atoi.c ft_utils.c threads_monitor.c philo.c threads_routine.c free_memory.c init_philo.c parse_input.c threads_utils.c
OBJS		:= $(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))
DEPS 		:= $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

-include $(DEPS)

$(BUILD_DIR)/%.o: %.c Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
.PHONY: all clean fclean re
