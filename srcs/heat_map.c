#include "../includes/filler.h"

int 	a(int n)
{
	return (n > 0 ? n : -1 * n);
}

int 	mdist(t_filler *filler, int i, int j)
{
	int min_d;
	int d;
	int y;
	int x;

	y = 0;
	min_d = MAXINT;
	while(filler->map->heat_map[y] && (y < filler->map->height))
	{

		x = 0;
		while (filler->map->heat_map[y][x] && x < filler->map->width)
		{
			if (filler->map->heat_map[y][x] == ENEMY_CELL && ((d = a(x - j) + a(y - i)) <= min_d))
				min_d = d;
			x++;
		}
		y++;
	}
	//printf("y: %d x: %d dist: %d\n", i, j, min_d);
	return (min_d);
}

void	fill_heat_map(t_filler *filler)
{
	int	i;
	int	j;

	i = 0;
	//printf("heat map1\n");
	while (filler->map->heat_map[i] && i < filler->map->height)
	{
		//printf("s\n");
		j = 0;
		while (filler->map->heat_map[i][j] && j < filler->map->width)
		{
			//printf("a\n");
			if (filler->map->heat_map[i][j] == EMPTY_CELL)
				filler->map->heat_map[i][j] = mdist(filler, i, j);
			j++;
		}

		i++;
	}
	//printf("heat map2\n");
}