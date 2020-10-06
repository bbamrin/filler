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
	filler->piece->x_top_left = 0;
	filler->piece->y_top_left = 0;
	filler->piece->th = 0;
	filler->piece->tw = 0;
	filler->map->width = 0;
	filler->map->height = 0;
	filler->piece->map = 0;
	filler->map->heat_map = 0;
}

int 	parse(t_filler *filler)
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
}

void	reset(t_filler *filler)
{
	heat_map_free(filler);
	piece_free(filler);
	reset_filler(filler);
}

int	main()
{
	t_filler	*filler;
	int			ret;

	if ((filler = init_filler()) == 0)
		return (ERROR_CODE);
	reset_filler(filler);
	if (parse_player(filler) == ERROR_CODE)
	{
		filler_free(filler);
		ft_putstr("player error\n");
		return (ERROR_CODE);
	}
	while ((ret = parse(filler)) == OK_CODE)
	{
		fill_heat_map(filler);
		place_piece(filler);
		ft_putnbr(filler->y);
		ft_putchar(' ');
		ft_putnbr(filler->x);
		ft_putchar('\n');
		reset(filler);
	}
	ft_putstr("ok\n");
	filler_free(filler);
}