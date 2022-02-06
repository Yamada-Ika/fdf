#include "fdf.h"

void	*ft_print_error(char *message)
{
	perror(message);
	return (NULL);
}

void	*ft_do_read_error_routine(char *p1, char *p2, char *p3, char *p4)
{
	all_free(p1, p2, p3, p4);
	return (ft_print_error("Cannot read file"));
}

void	*ft_do_malloc_error_routine(char *p1, char *p2, char *p3, char *p4)
{
	all_free(p1, p2, p3, p4);
	return (ft_print_error("Cannot allocate memmory"));
}

void	*ft_do_malloc_strs_error_routine(char **p1, char ***p2)
{
	free_strs(p1);
	free_char_map(p2);
	return (ft_print_error("Cannot allocate memmory"));
}
