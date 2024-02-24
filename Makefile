NAME		=	pipex

SRCS		=	pipex.c\
				errors.c\
				parsing.c\
				ft_split.c\
				pipex_utils.c\
				pipex_utils2.c\

BNS_SRCS	=	errors.c\
				parsing.c\
				ft_split.c\
				pipex_bonus.c\
				pipex_utils.c\
				pipex_utils2.c\
			  

# OBJS		= $(SRCS:%.c=%.o)

BNS_OBJS	= $(BNS_SRCS:%.c=%.o)

FLAGS		= -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	cc $(OBJS) -o $(NAME)

%.o : %.c pipex.h
	cc $(FLAGS) -c $<
	
clean:
	rm -f $(OBJS) $(BNS_OBJS)
	

bonus:$(BNS_OBJS)
	 cc $(FLAGS) $(BNS_OBJS) -o $(NAME)


fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean