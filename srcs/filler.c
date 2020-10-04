#include "../includes/filler.h"

int	main()
{
	t_filler *filler;

	if ((filler = init_filler()) == ERROR_CODE)
		return (ERROR_CODE);
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
			ft_putstr("map error\n");
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
		/*for (int g = 0; g < filler->map->height; ++g)
		{
			for (int k = 0; k < filler->map->width; ++k) {
				printf("%d ", filler->map->heat_map[g][k]);
			}
			printf("\n");
		}*/
		place_piece(filler);
		ft_putnbr(filler->x);
		ft_putchar(' ');
		ft_putnbr(filler->y);
		ft_putchar('\n');
		filler->x = 0;
		filler->y = 0;
		if (filler->piece && filler->piece->map)
		{
			char_tab_free(filler->piece->map, filler->piece->height);
			free(filler->piece->map);
		}
		if (filler->piece)
			free(filler->piece);
	}
	ft_putstr("ok\n");
	filler_free(filler);
}