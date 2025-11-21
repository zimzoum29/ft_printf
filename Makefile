NAME = libftprintf.a

CFLAGS = -Wall -Wextra -Werror -MMD -MP

INC = ft_printf.h

SRCS = ft_printf.c\
	utils.c\

AR = ar rcs

OBJ = $(SRCS:.c=.o)

ALL_D = $(SRCS:.c=.d)

all: $(NAME)

$(NAME): $(OBJ) $(INC) 
	$(AR) $(NAME) $(OBJ)

clean:
	rm -f $(OBJ) $(ALL_D)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(ALL_D)

.PHONY: all clean fclean re