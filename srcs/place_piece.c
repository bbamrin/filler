#include "../includes/filler.h"

int	calc_piece_sum(t_filler *filler, int x, int y)
{
	int	j;
	int	i;
	int	sum;
	int	pc;

	sum = 0;
	pc = 0;
	i = filler->piece->y_top_left - 1;
	//printf("%d %d %d %d\n", filler->piece->y_top_left, filler->piece->y_top_left + filler->piece->th,
	//	   filler->piece->x_top_left, filler->piece->x_top_left + filler->piece->tw);
	while (++i < filler->piece->y_top_left +  filler->piece->th)
	{
		j = filler->piece->x_top_left - 1;
		//printf("sumre :%d y: %d x: %d\n", sum, i , j);
		while (++j < filler->piece->x_top_left + filler->piece->tw)
		{

			if (filler->piece->map[i][j] == '*')
			{
				if (filler->map->heat_map[y + i % filler->piece->th][x + j % filler->piece->tw] == ENEMY_CELL)
					return (-1);
				if (filler->map->heat_map[y + i % filler->piece->th][x + j % filler->piece->tw] == PLAYER_CELL)
					pc++;
				sum += filler->map->heat_map[y + i % filler->piece->th][x + j % filler->piece->tw] == PLAYER_CELL;
				//printf("sum :%d y: %d x: %d\n", sum, y + (i % filler->piece->th), x + (j % filler->piece->tw));

			}
		}
	}
	sum = sum == PLAYER_CELL ? 0 : sum;
	return ((pc == 1) ? sum : -1);
}

void	place_piece(t_filler *filler)
{
	int	i;
	int	j;
	int sum;
	int min_sum;

	i = -1;
	min_sum = MAXINT;
	/*for (int k = 0; k < filler->map->height; ++k) {
		for (int l = 0; l < filler->map->width; ++l) {
			printf("%d ", filler->map->heat_map[k][l]);
		}
		printf("\n");
	}*/
	//printf("th: %d\n", filler->piece->th);
	while (++i <= filler->map->height - filler->piece->th)
	{
		j = -1;
		while (++j <= filler->map->width - filler->piece->tw)
		{
			//printf("i: %d j: %d\n",i, j);
			sum = calc_piece_sum(filler, j, i);
			if (sum >= 0 && sum < min_sum)
			{
				filler->x = j - filler->piece->x_top_left;
				filler->y = i - filler->piece->y_top_left;
				//printf("sum : %d\n", sum);
				min_sum = sum;
			}
		}
	}
}
