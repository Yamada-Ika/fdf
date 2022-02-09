CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
COPTS		:= -Ilibft -Llibft -lft -Iminilibx-linux -Lminilibx-linux -I/usr/X11/include -L/usr/X11/include/../lib -lXext -lX11 -lm

# libft
LIBFT_DIR	:= libft
LIBFT_A		:= libft.a
LIBFT_A		:= $(addprefix $(LIBFT_DIR)/, $(LIBFT_A))

# fdf
NAME		:= fdf
SRCS		:= calc_affine_matrix.c can_init_mlx.c can_read_map.c can_redisplay_map.c cord_point.c create_points.c degree_to_radian.c delete1.c delete2.c display_default_projection.c draw_line.c error1.c error2.c expose_hook.c free_utils.c get_map_size.c get_next_line.c get_next_line_utils.c help_option.c init_map_info.c init_points.c is_invalid_args1.c is_invalid_args2.c main.c math_utils.c new_matrix.c product_matrix.c put_map_to_image.c put_pixel.c set_matrix1.c set_matrix2.c update_map_points.c utils.c
OBJS		:= $(SRCS:%.c=%.o)
SRCS		:= $(addprefix src/, $(SRCS))
OBJS		:= $(addprefix obj/, $(OBJS))

# for bonus
ifdef WITH_BONUS
	SRCS		+= \
	src/install_hook_bonus.c   src/key_hook_utils_bonus.c\
	src/key_hook_bonus.c       src/mouse_hook_bonus.c src/can_display_map_bonus.c
	OBJS		+= \
	obj/install_hook_bonus.o   obj/key_hook_utils_bonus.o\
	obj/key_hook_bonus.o       obj/mouse_hook_bonus.o obj/can_display_map_bonus.o
else
	SRCS		+= src/install_hook.c src/key_hook.c src/can_display_map.c
	OBJS		+= obj/install_hook.o obj/key_hook.o obj/can_display_map.o
endif

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

bonus:
	make WITH_BONUS=1

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^ -Iinclude -Iminilibx-linux -Ilibft

$(MLX_A): empty
	make -C $(MLX_DIR)

clean:
	rm -rf obj/*.o
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
