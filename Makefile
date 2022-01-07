CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
COPTS	:= -Ilibft -Llibft -lft -Iminilibx-linux -I/usr/X11/include -Lminilibx-linux -lmlx_Darwin -L/usr/X11/include/../lib -lXext -lX11 -lm

# libft
LIBFT_DIR	:= libft
LIBFT_A		:= libft.a
LIBFT_A		:= $(addprefix $(LIBFT_DIR)/, $(LIBFT_A))

# fdf
NAME		:= fdf
SRCS		:= $(wildcard *.c)

# minilib
MLX_DIR	:= minilibx-linux
MLX_A	:= libmlx_Darwin.a
MLX_A	:= $(addprefix $(MLX_DIR)/, $(MLX_A))

all: $(NAME)

$(NAME): $(LIBFT_A) $(MLX_A) $(SRCS)
	$(CC) $(CFLAGS) $(COPTS) $(SRCS) -o $(NAME)

$(LIBFT_A): empty
	make -C $(LIBFT_DIR)

empty:

$(MLX_A): empty
	make -C $(MLX_DIR)

clean:
	rm -rf $(NAME)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re libft empty
