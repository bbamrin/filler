#include "../includes/filler.h"

int	validate_player(char **str_arr)
{
	if (strsplit_len(str_arr) != 5)
		return (ERROR_CODE);
	if (!ft_strequ(str_arr[0], "$$$")
		|| !ft_strequ(str_arr[1], "exec")
		|| !(ft_strequ(str_arr[2], "p1") || ft_strequ(str_arr[2], "p2"))
		|| !ft_strequ(str_arr[3], ":")
		|| str_arr[4][0] != '['
		|| !ft_strstr(str_arr[4], "pkathy.filler]"))
		return (ERROR_CODE);
	return (OK_CODE);
}

int validate_map_head(char **str_arr)
{
	if (strsplit_len(str_arr) != 3)
		return (ERROR_CODE);
	if (!ft_strequ(str_arr[0], "Plateau")
		|| ft_atoi(str_arr[1]) <= 0
		|| ft_atoi(str_arr[2]) <= 0
		|| !ft_strrchr(str_arr[2], ':'))
		return (ERROR_CODE);
	return (OK_CODE);
}

int	validate_map_neck(char *str, int width)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!((str[i] >= '0' && str[i] <= '9') || str[i] == ' '))
			return (ERROR_CODE);
	if (i != width)
		return (OK_CODE);
		//return (ERROR_CODE);
	return (OK_CODE);
}

int validate_map_body(char **str_arr, int width)
{
	int i;

	if (strsplit_len(str_arr) != 2)
		return (ERROR_CODE);
	if (validate_map_neck(str_arr[0], ft_strlen(str_arr[0])) == ERROR_CODE)
		return (ERROR_CODE);
	i = -1;
	while (str_arr[1][++i])
		if (!(ft_tolower(str_arr[1][i]) == 'o' || ft_tolower(str_arr[1][i]) == 'x' || str_arr[1][i] == '.'))
			return (ERROR_CODE);
	if (i != width)
		return (ERROR_CODE);
	return (OK_CODE);
}

int validate_piece_head(char **str_arr)
{
	if (strsplit_len(str_arr) != 3)
		return (ERROR_CODE);
	if (!ft_strequ(str_arr[0], "Piece")
		|| ft_atoi(str_arr[1]) <= 0
		|| ft_atoi(str_arr[2]) <= 0
		|| !ft_strrchr(str_arr[2], ':'))
		return (ERROR_CODE);
	return (OK_CODE);
}

int validate_piece_body(char *str, int width)
{
	int i;

	i = -1;
	while (str[++i])
		if (!(ft_tolower(str[i]) == '*' || str[i] == '.'))
			return (ERROR_CODE);
	if (i != width)
		return (ERROR_CODE);
	return (OK_CODE);
}