##
## Makefile for malloc in /home/soszyn_h/rendu/PSU/PSU_2016_malloc
## 
## Made by Hugo SOSZYNSKI
## Login   <hugo.soszynski@epitech.eu>
## 
## Started on  Mon Jan 23 13:30:30 2017 Hugo SOSZYNSKI
## Last update Thu Feb  9 10:30:29 2017 Hugo SOSZYNSKI
##

CC	= gcc

RM	= rm -f

CFLAGS	+= -Wextra -Wall -Werror
CFLAGS	+= -ggdb3
CFLAGS	+= -I.
CFLAGS	+= -fPIC -DPIC

LDFLAGS	=

NAME	= libmy_malloc.so

SRCS	= my_malloc.c \
	  my_free.c \
	  my_realloc.c \
	  my_calloc.c \
	  show_alloc_mem.c

OBJS	= $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -shared $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
