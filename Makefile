NAME			=	wshell
CFLAGS			=
CC				=	gcc
MAKE			=	make

READLINE_DIR	=	readline

HEADERS			=	wshell.h var_list/var_list.h
INCLUDE			=	-I . -I var_list -I $(READLINE_DIR)
LIB_DIRS		=	-L $(READLINE_DIR)
SRCS			=	wshell.c utils.c display.c handle_input.c \
					var_list/var_list.c var_list/var_list_fn.c

OBJS			=	$(patsubst %.c,%.o,$(SRCS))

all : $(NAME)

$(NAME): $(OBJS) readline
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB_DIRS) -lhistory -lreadline -ltermcap

%.o : %.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

readline:

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re readline
