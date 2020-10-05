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

int	main()
{
	t_filler *filler;

	if ((filler = init_filler()) == 0)
		return (ERROR_CODE);
	reset_filler(filler);
	if (parse_player(filler) == ERROR_CODE)
	{
		filler_free(filler);
		ft_putstr("player error\n");
		return (ERROR_CODE);
	}
	while (1)
	{
		if (parse_map(filler) == ERROR_CODE)
		{
			//ft_putstr("map error\n");
			filler_free(filler);
			return (ERROR_CODE);
		}
		if (parse_piece(filler) == ERROR_CODE)
		{
			ft_putstr("piece error\n");
			filler_free(filler);
			return (ERROR_CODE);
		}

		fill_heat_map(filler);
		/*for (int k = 0; k < filler->map->height; ++k) {
		for (int l = 0; l < filler->map->width; ++l) {
			printf("%d ", filler->map->heat_map[k][l]);
		}
		printf("\n");
		}*/
		place_piece(filler);
		ft_putnbr(filler->y);
		ft_putchar(' ');
		ft_putnbr(filler->x);
		ft_putchar('\n');
		heat_map_free(filler);
		piece_free(filler);
		reset_filler(filler);
	}
	ft_putstr("ok\n");
	filler_free(filler);
}