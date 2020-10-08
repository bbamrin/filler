#include "../includes/filler.h"

//написать
void	reset_filler(t_filler *filler)
{
	filler->y = 0;
	filler->x = 0;
	filler->piece->height = 0;
	filler->piece->width = 0;
	filler->piece->x_bottom_right = 0;
	filler->piece->y_bottom_right = 0;
	filler->piece->x_top_left = MAXINT;
	filler->piece->y_top_left = MAXINT;
	filler->piece->th = 0;
	filler->piece->tw = 0;
	filler->map->width = 0;
	filler->map->height = 0;
	filler->map->heat_map = 0;
	filler->piece->map = 0;
}

/*int 	parse(t_filler *filler)
{
	char *str;
	char **str_arr;

	str = 0;
	if(get_next_line(MODE, &str) <= 0)
		return (error_gnl(&str));
	if (!str)
		return (error_gnl(&str));
	str_arr = ft_strsplit(str, ' ');
	if	(validate_map_head(str_arr, filler) == ERROR_CODE)
		return (error_all(&str, &str_arr));
	ft_strdel(&str);
	if (get_next_line(MODE, &str) <= 0)
		return (error_all(&str, &str_arr));
	ft_strdel(&str);
	if (parse_map(str_arr, filler) == ERROR_CODE)
		return (error_all(&str, &str_arr));
	strsplit_free(&str_arr);
	if (get_next_line(MODE, &str) <= 0)
		return (error_gnl(&str));
	str_arr = ft_strsplit(str, ' ');
	if (validate_piece_head(str_arr) == ERROR_CODE)
		return (error_all(&str, &str_arr));
	if (parse_piece(str_arr, filler) == ERROR_CODE)
		return (error_all(&str, &str_arr));
	return (error_all(&str, &str_arr) - ERROR_CODE + OK_CODE);
}*/

void	reset(t_filler *filler)
{
	heat_map_free(filler);
	piece_free(filler);
	reset_filler(filler);
}

int		set_player(t_filler *filler, char **str)
{
	(*str) = 0;
	if (get_next_line(MODE, str) <= 0)
		return (0);
	if (ft_strlen((*str)) < 11) {
		free(*str);
		return (0);
	}
	filler->player = (*str)[10] == '1' ? 'o' : 'x';
	filler->enemy = filler->player == 'x' ? 'o' : 'x';
	return (1);
}
int		set_size(t_filler *filler, int mode, char **str)
{
	int 	i;

	i = 0;
	if (get_next_line(MODE, str) <= 0)
		return (0);

	while ((*str)[i] && !((*str)[i] >= '0' && (*str)[i] <= '9'))
		++i;

	if ((*str)[i] == 0)
		return (0);
	if (mode)
		filler->map->height = ft_atoi(&((*str)[i]));
	else
		filler->piece->height = ft_atoi(&((*str)[i]));
	while ((*str)[i] && ((*str)[i] >= '0' && (*str)[i] <= '9'))
		++i;
	if ((*str)[i] == 0)
		return (0);
	if (mode)
		filler->map->width = ft_atoi(&((*str)[i]));
	else
		filler->piece->width = ft_atoi(&((*str)[i]));

	return (1);
}

void 	clear_map(t_filler *filler)
{
	int i;

	i = -1;
	while (filler->map->heat_map && ++i < filler->map->height + 1)
		ft_memdel((void **)&(filler->map->heat_map[i]));
	ft_memdel((void  **)&(filler->map->heat_map));
	i = -1;
	while (filler->piece->map && ++i < filler->piece->height + 1)
		ft_memdel((void **)&(filler->piece->map[i]));
	ft_memdel((void **)&(filler->piece->map));
}

int		get_heat_map_cell(t_filler  *filler, char c)
{
	if (c == '.')
		return (EMPTY_CELL);
	if (ft_tolower(c) == filler->player)
		return (PLAYER_CELL);
	if (ft_tolower(c) == filler->enemy)
		return (ENEMY_CELL);
	return (ERROR_CODE);
}

int		set_map(t_filler *filler, char **str)
{
	int 	i;
	int		j;
	int 	k;

	i = -1;
	if (!(filler->map->heat_map = (int **)ft_memalloc(sizeof(int *) * (filler->map->height + 1))))
		return (0);
	while ((j = 0) == 0 && ++i < filler->map->height && get_next_line(MODE, str) > 0)
	{
		while ((*str)[j] && !((*str)[j] == 'X' || (*str)[j] == 'x' || (*str)[j] == 'o' || (*str)[j] == 'O' || (*str)[j] == '.'))
			j++;
		if ((k = -1) && (*str)[j] == 0)
			return (0);
		filler->map->heat_map[i] = (int *)ft_memalloc(sizeof(int) * (filler->map->width + 1));
		while ((*str)[j] && ++k < filler->map->width)
		{
			if (!((*str)[j] == 'X' || (*str)[j] == 'x' || (*str)[j] == 'o' || (*str)[j] == 'O' || (*str)[j] == '.'))
				return (0);
			filler->map->heat_map[i][k] = get_heat_map_cell(filler, (*str)[j++]);
		}
		ft_strdel(str);
	}
	return (1);
}

void	calc_size(int i, int j, t_filler *filler)
{
	//printf("i:%d j:%d y: %d, x %d\n", i , j, filler->piece->y_top_left, filler->piece->x_top_left);
	if (i < filler->piece->y_top_left)
		filler->piece->y_top_left = i;
	if (j < filler->piece->x_top_left)
		filler->piece->x_top_left = j;
	if (i > filler->piece->y_bottom_right)
		filler->piece->y_bottom_right = i;
	if (j > filler->piece->x_bottom_right)
		filler->piece->x_bottom_right = j;
	filler->piece->th = filler->piece->y_bottom_right - filler->piece->y_top_left + 1;
	filler->piece->tw = filler->piece->x_bottom_right - filler->piece->x_top_left + 1;
}
int		set_piece(t_filler *filler, char **str)
{
	int 	i;
	int		j;

	i = -1;
	if (!(filler->piece->map = (char **)ft_memalloc(sizeof(char *) * (filler->piece->height + 1))))
		return (0);
	while ((j = 0) == 0 && ++i < filler->piece->height && get_next_line(MODE, str) > 0)
	{
		filler->piece->map[i] = (char *)ft_memalloc(sizeof(char) * (filler->piece->width + 1));

		while ((*str)[j] && j < filler->piece->width)
		{
			if (!((*str)[j] == '.' || (*str)[j] == '*'))
				return (0);
			filler->piece->map[i][j] = (*str)[j];
			if ((*str)[j] == '*')
				calc_size(i, j, filler);
			j++;
		}
		ft_strdel(str);
	}
	return (1);
}

int parse(t_filler *filler, char **str)
{
	if (!set_size(filler, 1, str))
		return (0);
	ft_strdel(str);
	if (get_next_line(MODE, str) <= 0)
		return (0);
	ft_strdel(str);
	if (!set_map(filler, str))
		return (0);
	ft_strdel(str);
	if (!set_size(filler, 0, str))
		return (0);
	ft_strdel(str);
	if(!set_piece(filler, str))
	ft_strdel(str);
	return (1);
}

int	main()
{
	t_filler	*filler;
	char		*str;

	str = 0;
	if ((filler = init_filler()) == 0)
		return (ERROR_CODE);
	reset_filler(filler);
	if (!set_player(filler, &str))
	{
		filler_free(filler);
		ft_putstr("player error\n");
		return (ERROR_CODE);
	}
	ft_strdel(&str);
	while (parse(filler, &str))
	{
		if (filler->piece->y_top_left == MAXINT || filler->piece->x_top_left == MAXINT)
			break;
		place_piece(filler);
		ft_putnbr(filler->y);
		ft_putchar(' ');
		ft_putnbr(filler->x);
		ft_putchar('\n');
		ft_strdel(&str);
		clear_map(filler);
		reset_filler(filler);
	}
	clear_map(filler);
	ft_strdel(&str);
	ft_putstr("ok\n");
	filler_free(filler);
}