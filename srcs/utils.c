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
	int	i;

	i = -1;
	while (str_arr[++i])
		free(str_arr[i]);
	free(str_arr);
}

void	int_tab_free(int **tab, int height)
{
	int	i;

	i = -1;
	while (++i < height)
		free(tab[i]);
}

void	char_tab_free(char **tab, int height)
{
	int	i;

	i = -1;
	while (++i < height)
		free(tab[i]);
}

void	filler_free(t_filler *filler)
{
	if (filler->map && filler->map->heat_map)
	{
		int_tab_free(filler->map->heat_map, filler->map->height);
		free(filler->map->heat_map);
	}
	if (filler->map)
		free(filler->map);
	if (filler->piece && filler->piece->map)
	{
		char_tab_free(filler->piece->map, filler->piece->height);
		free(filler->piece->map);
	}
	if (filler->piece)
		free(filler->piece);
	free(filler);
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
