NAME = libftprintf.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -MMD -MP

INC = ft_printf.h

SRCS = ft_printf.c\

AR = ar rcs

OBJ = $(SRCS:.c=.o)

ALL_D = $(SRCS:.c=.d)

all: $(NAME)

$(NAME): $(OBJ) $(INC) Makefile
	$(AR) $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(ALL_D) .bonus_done

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(ALL_D)

.PHONY: all clean fclean re