CC			:= gcc
CFLAGS		:= -g -fsanitize=address #-Wall -Wextra -Werror
COPTS		:= -Ilibft -Llibft -lft -Iminilibx-linux -Lminilibx-linux -I/usr/X11/include -L/usr/X11/include/../lib -lXext -lX11 -lm

# libft
LIBFT_DIR	:= libft
LIBFT_A		:= libft.a
LIBFT_A		:= $(addprefix $(LIBFT_DIR)/, $(LIBFT_A))

# fdf
NAME		:= fdf
SRCS		:= \
affine_matrix.c              expose_hook.c                key_hook_utils.c\
can_display_map.c            free_utils.c                 main.c\
can_init_mlx.c               get_map_size.c               math_utils.c\
can_read_map.c               get_next_line.c              mouse_hook.c\
can_redisplay_map.c          get_next_line_utils.c        new_matrix.c\
cord_trans.c                 help_option.c                product_matrix.c\
create_points.c              init_points.c                put_map_to_image.c\
delete.c                     init_struct.c                put_pixel.c\
display_default_projection.c install_hook.c               set_matrix1.c\
draw_line.c                  is_invalid_args1.c           set_matrix2.c\
error.c                      is_invalid_args2.c           update_map_points.c\
error2.c                     key_hook.c                   utils.c
OBJS		:= $(SRCS:%.c=%.o)
SRCS		:= $(addprefix src/, $(SRC))
OBJS		:= $(addprefix obj/, $(OBJS))

# for malloc error check test
ifdef MALLOC_FAILE_TEST
SRCS		+= test/malloc_faile_func.c
OBJS		+= test/malloc_faile_func.o
endif

# minilib
MLX_DIR		:= minilibx-linux
ifeq ($(shell uname), Linux)
	MLX_A	:= libmlx_Linux.a
	COPTS	+= -lmlx_Linux
else ifeq ($(shell uname), Darwin)
	MLX_A	:= libmlx_Darwin.a
	COPTS	+= -lmlx_Darwin
endif
MLX_A	:= $(addprefix $(MLX_DIR)/, $(MLX_A))

all: $(NAME)

ifeq ($(shell uname), Linux)
$(NAME): $(LIBFT_A) $(MLX_A) $(OBJS)
	$(CC) -Wl,-start-group $(CFLAGS) $(COPTS) $(OBJS) -o $(NAME) -Wl,-end-group
else ifeq ($(shell uname), Darwin)
$(NAME): $(LIBFT_A) $(MLX_A) $(OBJS)
	$(CC) $(CFLAGS) $(COPTS) $(OBJS) -o $(NAME)
endif

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

malloc:
	touch src/*.c
	make MALLOC_FAILE_TEST=1

norm_dir=$$(ls | grep -v minilibx-linux)
norm:
	norminette $(norm_dir)

.PHONY: all clean fclean re libft empty
