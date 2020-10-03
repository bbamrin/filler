#include "../includes/filler.h"

int		parse_player(t_filler *filler)
{
	char	*str;
	char	**str_arr;

	if (get_next_line(1, &str) < 0)
		return (ERROR_CODE);
	if (!(str_arr = ft_strsplit(str, ' ')))
		return (ERROR_CODE);
	if (validate_player(str_arr) == ERROR_CODE)
	{
		free(str);
		strsplit_free(str_arr);
		return (ERROR_CODE);
	}
	if(str_arr[2][1] == '1')
	{
		filler->player = 'o';
		filler->enemy = 'x';
	}
	else
	{
		filler->player = 'x';
		filler->enemy = 'o';
	}
	free(str);
	return (OK_CODE);
}

int		get_heat_map_cell(char c)
{
	if (c == '.')
		return (EMPTY_CELL);
	if (c == filler->player)
		return (PLAYER_CELL);
	if (c == filler->player)
		return (ENEMY_CELL);
}

int		parse_map_body(t_filler *filler)
{
	int		i;
	int		j;
	char	*str;
	char 	**str_arr;

	i = -1;
	while (++i < filler->map->height && (j = -1) == -1)
	{
		if (get_next_line(1, &str) < 0)
			return (ERROR_CODE);
		if (!(str_arr = ft_strsplit(str, ' ')))
			return (error_gnl(str));
		if (validate_map_body(str_arr) == ERROR_CODE)
			return (error_all(str, str_arr));
		while (++j < filler->map->width)
			filler->map->heat_map[i][j] = get_heat_map_cell(str_arr[1][j]);
		strsplit_free(str_arr);
		free(str);
	}
	return (OK_CODE);
}

int		parse_map(t_filler *filler)
{
	char	*str;
	char	**str_arr;

	if (get_next_line(1, &str) < 0)
		return (ERROR_CODE);
	if (!(str_arr = ft_strsplit(str, ' ')))
		return (error_gnl(str));
	if	(validate_map_head(str_arr) == ERROR_CODE)
		return (error_all(str,str_arr));
	free(str);
	filler->map->height = ft_atoi(str_arr[1]);
	filler->map->width = ft_atoi(str_arr[2]);
	strsplit_free(str_arr);
	if (get_next_line(1, &str) < 0)
		return (ERROR_CODE);
	if (validate_map_neck(str) == ERROR_CODE)
		return (error_gnl(str));
	free(str);
	if (init_heat_map(filler) == ERROR_CODE)
		return (ERROR_CODE);
	return (parse_map_body(filler));
}

int 	parse_piece_body(t_filler *filler)
{
	int		i;

	i = -1;
	if (!(filler->piece->map = (char **)ft_memalloc(sizeof(char *) * filler->piece->height)))
		return (ERROR_CODE);
	while (++i < filler->piece->height && (j = -1) == -1)
	{
		if (get_next_line(1, &(filler->piece->map[i])) < 0)
			return (error_piece(filler));
		if (validate_piece_body(filler->piece->map[i]) == ERROR_CODE)
			return (error_piece(filler));
	}
	return (OK_CODE);
}

int		parse_piece(t_filler *filler)
{
	char	*str;
	char	**str_arr;

	if (get_next_line(1, &str) < 0)
		return (ERROR_CODE);
	if (!(str_arr = ft_strsplit(str, ' ')))
		return (error_gnl(str));
	if	(validate_piece_head(str_arr) == ERROR_CODE)
		return (error_all(str,str_arr));
	free(str);
	filler->piece->height = ft_atoi(str_arr[1]);
	filler->piece->width = ft_atoi(str_arr[2]);
	strsplit_free(str_arr);
	return (parse_piece_body(filler));
}
