#include "../includes/filler.h"

int	validate_player(char **str_arr)
	if (strsplit_len(str_arr) < 5)
		return (ERROR_CODE);
	if (!ft_strequ(str_arr[0], "$$$")
		|| !ft_strequ(str_arr[1], "exec")
		|| !ft_strequ(str_arr[2], "p1")
		|| !ft_strequ(str_arr[2], "$$$")
		|| !ft_strequ(str_arr[3], ":")
		|| !ft_strequ(str_arr[4], "[pkathy.filler]"))
		return (ERROR_CODE);
	return (OK_CODE);
}

int validate_map_head(char **str_arr)
{
	return (OK_CODE);
}

int	validate_map_neck(char *str)
{
	return (OK_CODE);
}

int validate_map_body(char **str_arr)
{
	return (OK_CODE);
}

int validate_piece_head(char **str_arr)
{
	return (OK_CODE);
}

int validate_piece_body(char *str)
{
	return (OK_CODE);
}