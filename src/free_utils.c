#include "fdf.h"

void	all_free(void *p1, void *p2, void *p3, void *p4)
{
	free(p1);
	free(p2);
	free(p3);
	free(p4);
}

void	free_tristrs(char ***strs)
{
	size_t	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free_strs(strs[i]);
		i++;
	}
	free(strs);
}

void	free_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}
