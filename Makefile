NAME		=	pipex
NAME_BNS	=	pipex_bonus

SRCS		=	pipex.c\
				errors.c\
				parsing.c\
				ft_split.c\
				syscalls.c\
				pipex_helpers.c\
				pipex_helpers2.c\
				get_next_line_utils.c

BNS_SRCS	=	errors.c\
				parsing.c\
				ft_split.c\
				syscalls.c\
				heredoc_utils.c\
				heredoc.c\
				pipex_bonus.c\
				pipex_helpers.c\
				bonus_helpers.c\
				bonus_helpers2.c\
				get_next_line.c\
				pipex_helpers2.c\
				get_next_line_utils.c


OBJS		= $(SRCS:%.c=%.o)

BNS_OBJS	= $(BNS_SRCS:%.c=%.o)

FLAGS		= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	cc $(OBJS) -o $(NAME)

bonus: $(NAME_BNS)

$(NAME_BNS): $(BNS_OBJS)
	cc $(FLAGS) $(BNS_OBJS) -o $(NAME_BNS)

%.o : %.c pipex.h
	cc $(FLAGS) -c $<

clean:
	rm -f $(OBJS) $(BNS_OBJS)
	
fclean: clean
	rm -f $(NAME) $(NAME_BNS)

re: fclean all

.PHONY: clean
