#include "../includes/filler.h"

t_filler	*init_filler()
{
	t_filler	*ret;

	if ((ret = (t_filler *)ft_memalloc(sizeof(t_filler))))
	{
		ret->player = 0;
		ret->enemy = 0;
		ret->x = 0;
		ret->y = 0;
		if (!(ret->map = (t_map *)ft_memalloc(sizeof(t_map))))
		{
			free(ret);
			return (0);
		}
		if (!(ret->piece = (t_piece *)ft_memalloc(sizeof(t_piece))))
		{
			free(ret->map);
			free(ret);
			return (0);
		}
		ret->map->heat_map = 0;
		ret->piece->height = 0;
		return (ret);
	}
	return (0);
}


int			init_heat_map(t_filler *filler)
{
	int	i;

	i = -1;
	if (filler->map->heat_map == 0)
	{
		if (!(filler->map->heat_map = (int **)ft_memalloc(sizeof(int *) * filler->map->height)))
			return (ERROR_CODE);
		while (++i < filler->map->height)
			if (!(filler->map->heat_map[i] = (int *)ft_memalloc(sizeof(int) * filler->map->width)))
				return (ERROR_CODE);
	}
	return (OK_CODE);
	//creates map with size x*y
}