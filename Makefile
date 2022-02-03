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
arg_utils.c           get_next_line_utils.c\
check_leak.c          hook.c\
cord_trans.c          hook_utils1.c\
display_map.c         init_struct.c\
draw_line.c           main.c\
error.c               map_utils.c\
free_utils.c          math_utils.c\
ft_read_map.c         matrix_utils.c\
ft_set_projection.c   put_pixel.c\
get_next_line.c
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
