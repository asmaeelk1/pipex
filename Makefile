NAME		=	pipex

SRCS		=	errors.c\
				ft_split.c\
				parsing.c\
				pipex_utils.c\
				pipex_utils2.c\
				pipex.c\

# BNS_SRCS	= 
			  

OBJS		= $(SRCS:%.c=%.o)

# BNS_OBJS	= $(BNS_SRCS:%.c=%.o)

FLAGS		= -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	cc $(OBJS) -o $(NAME)


%.o : %.c pipex.h
	cc $(FLAGS) -c $<
	
clean:
	rm -f $(OBJS) $(BNS_OBJS)
	

# bonus:$(BNS_OBJS)
# 	 ar rc $(NAME) $(BNS_OBJS)


fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean