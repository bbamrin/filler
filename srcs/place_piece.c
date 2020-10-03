#include "../includes/filler.h"

int	calc_piece_sum(t_filler *filler, int x, int y)
{
	int	j;
	int	i;
	int	sum;
	int	pc;

	sum = 0;
	pc = 0;
	j = -1;
	while (++j < filler->piece->true_height)
	{
		i = -1;
		while (++i < filler->piece->true_width)
			if (filler->piece->map[j][i] == '*')
			{
				if (filler->map->heat_map[y + j][x + i] == ENEMY_CELL)
					return (-1);
				if (filler->map->heat_map[y + j][x + i] == PLAYER_CELL)
					pc++;
				sum += filler->map->heat_map[y + j][x + i];
			}
	}
	return ((pc == 1) ? sum : -1);
}

int	place_piece(t_filler *filler)
{
	int	i;
	int	j;
	int sum;
	int min_sum;

	i = -1;
	min_sum = MAXINT;
	while (++i <= filler->map->height - filler->piece->true_height)
	{
		j = -1;
		while (++j <= filler->map->width - filler->piece->true_width)
		{
			sum = calc_piece_sum(filler, j, i);
			if (sum >= 0 && sum < min_sum)
			{
				filler->x = j - filler->piece->x_top_left;
				filler->y = i - filler->piece->y_top_left;
				min_sum = sum;
			}
		}
	}
}
