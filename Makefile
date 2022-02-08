CC			:= cc
CFLAGS		:= -g -fsanitize=address -Wall -Wextra -Werror
COPTS		:= -Ilibft -Llibft -lft -Iminilibx-linux -Lminilibx-linux -I/usr/X11/include -L/usr/X11/include/../lib -lXext -lX11 -lm

# libft
LIBFT_DIR	:= libft
LIBFT_A		:= libft.a
LIBFT_A		:= $(addprefix $(LIBFT_DIR)/, $(LIBFT_A))

# fdf
NAME		:= fdf
SRCS		:= \
calc_affine_matrix.c         draw_line.c                  init_points.c                product_matrix.c\
can_display_map.c            error1.c                     install_hook.c               put_map_to_image.c\
can_init_mlx.c               error2.c                     is_invalid_args1.c           put_pixel.c\
can_read_map.c               expose_hook.c                is_invalid_args2.c           set_matrix1.c\
can_redisplay_map.c          free_utils.c                 key_hook.c                   set_matrix2.c\
cord_point.c                 get_map_size.c               key_hook_utils.c             update_map_points.c\
create_points.c              get_next_line.c              main.c                       utils.c\
delete1.c                    get_next_line_utils.c        math_utils.c\
delete2.c                    help_option.c                mouse_hook.c\
display_default_projection.c init_map_info.c              new_matrix.c
OBJS		:= $(SRCS:%.c=%.o)
SRCS		:= $(addprefix src/, $(SRC))
OBJS		:= $(addprefix obj/, $(OBJS))

# for malloc error check test
ifdef MALLOC_FAILE_TEST
SRCS		+= test/malloc_faile.c
OBJS		+= test/malloc_faile.o
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
	rm -rf test/malloc_faile.o

norm_dir=$$(ls | grep -v minilibx-linux)
norm:
	norminette $(norm_dir)

.PHONY: all clean fclean re libft empty
