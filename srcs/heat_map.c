#include "../includes/filler.h"

int 	ft_abs(int n)
{
	return (n > 0 ? n : -1 * n);
}

int 	calc_dist(t_filler *filler, int i, int j)
{
	int min_d;
	int d;
	int y;
	int x;

	y = -1;
	min_d = MAXINT;
	while(++y < filler->map->height)
	{
		x = -1;
		while (++x < filler->map->width)
			if (filler->map->heat_map[y][x] == ENEMY_CELL && ((d = ft_abs(x - j) + ft_abs(y - i)) <= min_d))
				min_d = d;
	}
	return (min_d);
}

void	fill_heat_map(t_filler *filler)
{
	int	i;
	int	j;

	i = -1;
	while (++i < filler->map->height)
	{
		j = -1;
		while (++j < filler->map->width)
			if (filler->map->heat_map[i][j] == EMPTY_CELL)
				filler->map->heat_map[i][j] = calc_dist(filler, i, j);
	}
}