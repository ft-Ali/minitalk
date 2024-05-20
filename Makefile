CLIENT_NAME	=	client
SERVER_NAME	=	server

CC			=	cc
FLAG		=	-Wall -Wextra -Werror -g3

LIBFT_PATH	=	.libft
LIBFT_FILE	=	libft.a
LIBFT_LIB	=	$(LIBFT_PATH)/$(LIBFT_FILE)

CLIENT_SRC	=	srcs/client.c
SERVER_SRC	=	srcs/server.c

CLIENT_OBJ	=	$(CLIENT_SRC:.c=.o)
SERVER_OBJ	=	$(SERVER_SRC:.c=.o)

.c.o:
	@printf "\r\033[K[Minitalk] \033[0;32mBuilding : $<\033[0m"
	@$(CC) $(FLAG) -c $< -o $@

all:	$(CLIENT_NAME) $(SERVER_NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_PATH)

$(CLIENT_NAME): $(LIBFT_LIB) $(CLIENT_OBJ)
	@printf "\r\033[K[client] \033[0;32mLinking...\033[0m"
	@$(CC) $(CLIENT_OBJ) $(LIBFT_LIB) -o $(CLIENT_NAME) -lm 
	@printf "\r\033[K[client] \033[0;32mDone!\033[0m\n"

$(SERVER_NAME): $(LIBFT_LIB) $(SERVER_OBJ)
	@printf "\r\033[K[server] \033[0;32mLinking...\033[0m"
	@$(CC) $(SERVER_OBJ) $(LIBFT_LIB) -o $(SERVER_NAME) -lm
	@printf "\r\033[K[server] \033[0;32mDone!\033[0m\n"

clean:
	@make clean -sC $(LIBFT_PATH)
	@rm -f $(CLIENT_OBJ) $(SERVER_OBJ)
	@printf "[Minitalk] \033[1;31mCleaned .o!\033[0m\n"

fclean: clean
	@rm -f $(CLIENT_NAME) $(SERVER_NAME)
	@make fclean -C $(LIBFT_PATH)
	@printf "[Minitalk] \033[1;31mCleaned all!\033[0m\n"

re: fclean all

.PHONY: all clean fclean re