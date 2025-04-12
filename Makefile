SERVER_SRC = server.c
CLIENT_SRC = client.c
SERVER_BONUS_SRC = server_bonus.c
CLIENT_BONUS_SRC = client_bonus.c

PRNTF_SRC = ft_printf/ft_printf.c ft_printf/ft_putchar.c ft_printf/ft_put_hex_upper.c \
             ft_printf/ft_putnbr_unsigned.c ft_printf/ft_putstr.c ft_printf/ft_put_hex_lower.c \
             ft_printf/ft_putnbr.c ft_printf/ft_put_pointer.c

PRNTF_OBJ = $(PRNTF_SRC:.c=.o)
SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SERVER_BONUS_OBJ = $(SERVER_BONUS_SRC:.c=.o)
CLIENT_BONUS_OBJ = $(CLIENT_BONUS_SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: server client

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

server: $(SERVER_OBJ) $(PRNTF_OBJ)
	$(CC) $(CFLAGS) $(SERVER_OBJ) $(PRNTF_OBJ) -o server

client: $(CLIENT_OBJ) $(PRNTF_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) $(PRNTF_OBJ) -o client

bonus: server_bonus client_bonus

server_bonus: $(SERVER_BONUS_OBJ) $(PRNTF_OBJ)
	$(CC) $(CFLAGS) $(SERVER_BONUS_OBJ) $(PRNTF_OBJ) -o server_bonus

client_bonus: $(CLIENT_BONUS_OBJ) $(PRNTF_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_BONUS_OBJ) $(PRNTF_OBJ) -o client_bonus

clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ) $(PRNTF_OBJ) $(SERVER_BONUS_OBJ) $(CLIENT_BONUS_OBJ)

fclean: clean
	rm -f server client server_bonus client_bonus

re: fclean all

.PHONY: all bonus clean fclean re



