#include "../includes/filler.h"

int	main(int argc, char **argv)
{
	t_filler *filler;

	if ((filler = init_filler()) == ERROR_CODE)
		return (ERROR_CODE);
	if (parse_player(filler) == ERROR_CODE)
	{
		//free filler
		printf("player error");
		return (ERROR_CODE);
	}
	/*if (parse_map(filler) == ERROR_CODE)
	{
		printf("map error");
		return (ERROR_CODE);
	}*/
}