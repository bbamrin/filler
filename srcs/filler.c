#include "../includes/filler.h"

int	main(int argc, char **argv)
{
	t_filler *filler;

	if ((filler = init_filler()) == ERROR_CODE)
		return (ERROR_CODE);
	/*if (parse_player(filler) == ERROR_CODE)
	{
		filler_free(filler);
		ft_putstr("player error\n");
		return (ERROR_CODE);
	}*/
	/*if (parse_map(filler) == ERROR_CODE)
	{
		filler_free(filler);
		ft_putstr("map error\n");
		return (ERROR_CODE);
	}*/
	if (parse_piece(filler) == ERROR_CODE)
	{
		filler_free(filler);
		ft_putstr("map error\n");
		return (ERROR_CODE);
	}
	ft_putstr("ok\n");
	filler_free(filler);
}