// #include "fdf.h"

#include <stddef.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"
#include <time.h>
#include <stdio.h>

#define RANDOM_PARAM 2

char	**my_ft_split(char *s, char c)
{
	srand((unsigned int)time(NULL));
	if (rand() % RANDOM_PARAM == 0)
		return (NULL);
	return (ft_split(s, c));
}

void	*my_ft_calloc(size_t n, size_t size)
{
	srand((unsigned int)time(NULL));
	if (rand() % RANDOM_PARAM == 0)
		return (NULL);
	return (ft_calloc(n, size));
}

void	*my_mlx_init(void)
{
	srand((unsigned int)time(NULL));
	if (rand() % RANDOM_PARAM == 0)
		return (NULL);
	return (mlx_init());
}

void	*my_mlx_new_window(void *xvar,int size_x,int size_y,char *title)
{
	srand((unsigned int)time(NULL));
	if (rand() % RANDOM_PARAM == 0)
		return (NULL);
	return (mlx_new_window(xvar, size_x, size_x, title));
}

void	*my_mlx_new_image(void *xvar,int width, int height)
{
	srand((unsigned int)time(NULL));
	if (rand() % RANDOM_PARAM == 0)
		return (NULL);
	return (mlx_new_image(xvar, width, height));
}

