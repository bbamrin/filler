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

void	strsplit_free(char ***str_arr)
{
	int	i;

	if (str_arr && *str_arr)
	{
		i = -1;
		while ((*str_arr)[++i])
			ft_strdel(&((*str_arr)[i]));
		//mb leak
		free(*str_arr);
		*str_arr = NULL;
	}
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
		ft_strdel(&(tab[i]));
}

void	heat_map_free(t_filler *filler)
{
	if (filler->map && filler->map->heat_map)
	{
		//printf("h\n");
		int_tab_free(filler->map->heat_map, filler->map->height);
		free(filler->map->heat_map);
		filler->map->heat_map = 0;
		//filler->map = 0;
	}
}

void	piece_free(t_filler *filler)
{
	if (filler->piece && filler->piece->map)
	{
		//printf("ph: %d\n", filler->piece->height);
		char_tab_free(filler->piece->map, filler->piece->height);
		free(filler->piece->map);
		filler->piece->map = 0;
		//filler->piece = 0;
	}
}

void	filler_free(t_filler *filler)
{
	heat_map_free(filler);
	if (filler->map)
		free(filler->map);
	piece_free(filler);
	if (filler->piece)
		free(filler->piece);
	free(filler);
}

int		error_gnl(char **str)
{
	ft_strdel(str);
	return (ERROR_CODE);
}

int		error_strsplit(char **str_arr)
{
	strsplit_free(&str_arr);
	return (ERROR_CODE);
}

int 	error_all(char **str, char ***str_arr)
{
	ft_strdel(str);
	strsplit_free(str_arr);
	return (ERROR_CODE);
}
