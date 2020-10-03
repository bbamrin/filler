#include "../includes/filler.h"

int		strsplit_len(char **str_arr)
{
	int i = 0;
	while (*str_arr)
	{
		i++;
		str_arr++;
	}
	return (i);
}

void	strsplit_free(char **str_arr)
{
	while (*str_arr)
	{
		free(*str_arr);
		str_arr++;
	}
	free(str_arr);
}

void	heat_map_free(int	**heat_map, int height)
{
	int	i;

	i = -1;
	while (++i < height)
		free(heat_map[i]);
}

int		error_gnl(char *str)
{
	free(str);
	return (ERROR_CODE);
}

int		error_strsplit(char **str_arr)
{
	strsplit_free(str_arr);
	return (ERROR_CODE);
}

int 	error_all(char *str, char **str_arr)
{
	free(str);
	strsplit_free(str_arr);
	return (ERROR_CODE);
}

int		error_piece(t_filler *filler)
{
	return (ERROR_CODE);
}
