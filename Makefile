CC				:= gcc
CFLAGS			:= #-g -fsanitize=address #-Wall -Wextra -Werror
COPTS			:= -Ilibft -Llibft -lft -Iminilibx-linux -I/usr/X11/include -Lminilibx-linux -lmlx_Darwin -L/usr/X11/include/../lib -lXext -lX11 -lm

# libft
LIBFT_DIR	:= libft
LIBFT_A		:= libft.a
LIBFT_A		:= $(addprefix $(LIBFT_DIR)/, $(LIBFT_A))

# fdf
NAME		:= fdf
SRCS		:= \
affine_matrix.c       error.c               init_struct.c\
arg_utils.c           free_utils.c          main.c\
check_leak.c          ft_read_map.c         map_utils.c\
cord_trans.c          ft_set_projection.c   math_utils.c\
create_map.c          get_next_line.c       new_matrix.c\
debug_utils.c         get_next_line_utils.c product_matrix.c\
display_map.c         hook.c                put_pixel.c\
draw_line.c           hook_utils1.c         set_matrix.c
OBJS		:= $(SRCS:%.c=%.o)
SRCS		:= $(addprefix src/, $(SRC))
OBJS		:= $(addprefix obj/, $(OBJS))

# for memory leaks check
ifdef LEAK_CHECK
SRCS		+= src/check_leak.c
OBJS		+= obj/check_leak.o
endif

# minilib
MLX_DIR	:= minilibx-linux
MLX_A	:= libmlx_Darwin.a
MLX_A	:= $(addprefix $(MLX_DIR)/, $(MLX_A))

all: $(NAME)

$(NAME): $(LIBFT_A) $(MLX_A) $(OBJS)
	$(CC) $(CFLAGS) $(COPTS) $(OBJS) -o $(NAME)

$(LIBFT_A): empty
	make -C $(LIBFT_DIR)

empty:

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^ -Iinclude -Iminilibx-linux -Ilibft

$(MLX_A): empty
	make -C $(MLX_DIR)

clean:
	rm -rf $(OBJS)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

leak:
	touch src/check_leak.c
	make LEAK_CHECK=1

norm_dir=$$(ls | grep -v minilibx-linux)
norm:
	norminette $(norm_dir)

.PHONY: all clean fclean re libft empty
