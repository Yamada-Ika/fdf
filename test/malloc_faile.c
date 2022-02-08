#include <stddef.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"
#include <time.h>
#include <stdio.h>

#define RANDOM_PARAM 11

char	**test1(char *s, char c)
{
	srand((unsigned int)time(NULL));
	if (rand() % RANDOM_PARAM == 0)
		return (NULL);
	return (ft_split(s, c));
}

void	*test2(size_t n, size_t size)
{
	srand((unsigned int)time(NULL));
	if (rand() % RANDOM_PARAM == 0)
		return (NULL);
	return (ft_calloc(n, size));
}

void	*test3(void)
{
	srand((unsigned int)time(NULL));
	if (rand() % RANDOM_PARAM == 0)
		return (NULL);
	return (mlx_init());
}

void	*test4(void *xvar, int size_x, int size_y, char *title)
{
	srand((unsigned int)time(NULL));
	if (rand() % RANDOM_PARAM == 0)
		return (NULL);
	return (mlx_new_window(xvar, size_x, size_y, title));
}

void	*test5(void *xvar, int width, int height)
{
	srand((unsigned int)time(NULL));
	if (rand() % RANDOM_PARAM == 0)
		return (NULL);
	return (mlx_new_image(xvar, width, height));
}
