CFLAGS= -Wall -Werror -Wextra
CC= cc
NAME=philo
SRCS= ft_atoi.c ft_utils.c threads_monitor.c philo.c threads_routine.c free_memory.c init_philo.c
OBJS= $(SRCS:.c=.o)
INCS= philo.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
.PHONY: all clean fclean re