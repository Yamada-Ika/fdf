#include "fdf.h"

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
