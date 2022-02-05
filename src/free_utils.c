#include "fdf.h"

void	all_free(void *p1, void *p2, void *p3, void *p4)
{
	free(p1);
	free(p2);
	free(p3);
	free(p4);
}

void	free_char_map(char ***map)
{
	size_t	i;

	if (map == NULL)
		return ;
	i = 0;
	while (map[i] != NULL)
	{
		free_strs(map[i]);
		i++;
	}
	free(map);
}

void	free_strs(char **strs)
{
	size_t	i;

	if (strs == NULL)
		return ;
	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}
