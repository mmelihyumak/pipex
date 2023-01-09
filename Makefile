SRCS	=		childs.c error.c ft_split.c ft_strjoin.c ft_strncmp.c pipex.c free.c 
 
OBJS	=		$(SRCS:.c=.o)

NAME	=		pipex

CC		=		gcc

RM		=		rm -rf

CFLAGS	=		-Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(OBJS) 
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:	
		$(RM) $(OBJS)

fclean:		clean 
					$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re