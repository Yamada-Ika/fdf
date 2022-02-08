CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
COPTS		:= -Ilibft -Llibft -lft -Iminilibx-linux -Lminilibx-linux -I/usr/X11/include -L/usr/X11/include/../lib -lXext -lX11 -lm

# libft
LIBFT_DIR	:= libft
LIBFT_A		:= libft.a
LIBFT_A		:= $(addprefix $(LIBFT_DIR)/, $(LIBFT_A))

# fdf
NAME		:= fdf
SRCS		:= \
calc_affine_matrix.c         draw_line.c                  init_map_info.c              mouse_hook.c\
can_display_map.c            error1.c                     init_points.c                new_matrix.c\
can_init_mlx.c               error2.c                     install_hook.c               product_matrix.c\
can_read_map.c               expose_hook.c                is_invalid_args1.c           put_map_to_image.c\
can_redisplay_map.c          free_utils.c                 is_invalid_args2.c           put_pixel.c\
cord_point.c                 get_map_size.c               key_hook.c                   set_matrix1.c\
create_points.c              get_next_line.c              key_hook_utils.c             set_matrix2.c\
delete.c                     get_next_line_utils.c        main.c                       update_map_points.c\
display_default_projection.c help_option.c                math_utils.c                 utils.c
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
