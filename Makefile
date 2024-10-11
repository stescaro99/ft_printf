NAME = libftprintf.a
SOURCES = ft_printf.c utils.c ft_itoa_base.c handle_space.c \
			libft_utils.c convert_to_char.c ft_print_w_flags.c
	
OBJECTS = $(SOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar

all: $(NAME)

$(NAME): $(OBJECTS)
	$(AR) -src $@ $?

%.o: %.c
	$(CC) -c $(CFLAGS) $?

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all

fast:		all clean
			clear
			@echo "$(GREEN)$(NAME) created[0m ✔️"
			
eval:		fast
			code .
			clear
			norminette

push:		fclean
			git add .
			git commit -m "push"
			git push
			clear

.PHONY: all clean fclean re bonus
