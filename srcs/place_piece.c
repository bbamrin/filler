#include "../includes/filler.h"

int	calc_piece_sum(t_filler *filler, int x, int y)
{
	int	j;
	int	i;
	int	sum;

	//printf("------------piece sum1--------------------------\n");
	sum = 0;
	i = filler->piece->y_top_left;
	while (i >=0 && filler->map->heat_map[i] && i < filler->piece->y_top_left + filler->piece->th)
	{
		j = filler->piece->x_top_left;//printf("here!1 %d\n", j);
		while (j >=0 && filler->map->heat_map[i][j] && j < filler->piece->x_top_left + filler->piece->tw)
		{
			if (filler->piece->map[i][j] == '*')
			{
				//printf("y: %d x: %d\n", y + i - filler->piece->y_top_left,x + j - filler->piece->x_top_left);
				//printf("%d\n", filler->map->heat_map[y + i - filler->piece->y_top_left][x + j - filler->piece->x_top_left]);
				if (filler->map->heat_map[y + i - filler->piece->y_top_left][x + j - filler->piece->x_top_left] == EMPTY_CELL)
					filler->map->heat_map[y + i - filler->piece->y_top_left][x + j - filler->piece->x_top_left]
							= mdist(filler, y + i - filler->piece->y_top_left, x + j - filler->piece->x_top_left);
				if (filler->map->heat_map[y + i - filler->piece->y_top_left][x + j - filler->piece->x_top_left] != PLAYER_CELL)
					sum += filler->map->heat_map[y + i - filler->piece->y_top_left][x + j - filler->piece->x_top_left];
			}
			j++;
		}
		i++;
	}
	//printf("-------------piece sum2: %d ----------------------------------\n", sum);
	return (sum);
}

int		is_fit(t_filler *filler, int x, int y)
{
	int	j;
	int	i;
	int	pc;
	//printf("piece sum1\n");
	pc = 0;
	i = filler->piece->y_top_left;
	//printf("y: %d, x: %d\n", y, x);
	//printf("y1: %d, x1: %d\n", y - filler->piece->y_top_left, x - filler->piece->x_top_left);
	while (i >=0 && filler->map->heat_map[i] && i < filler->piece->y_top_left + filler->piece->th)
	{
		j = filler->piece->x_top_left;//printf("here!1 %d\n", j);
		while (j >=0 && filler->map->heat_map[i][j] && j < filler->piece->x_top_left + filler->piece->tw)
		{
			if (filler->piece->map[i][j] == '*')
			{
				//printf("y: %d, x: %d\n", y + i - filler->piece->y_top_left, x + j - filler->piece->x_top_left);
				if (filler->map->heat_map[y + i - filler->piece->y_top_left][x + j - filler->piece->x_top_left] == ENEMY_CELL)
					return (0);
				if (filler->map->heat_map[y + i - filler->piece->y_top_left][x + j - filler->piece->x_top_left] == PLAYER_CELL)
					pc++;
				//sum += filler->map->heat_map[y + i - filler->piece->y_top_left][x + j - filler->piece->x_top_left];

			}
			j++;
		}//printf("here!2 %d\n", j);
		i++;
	}
	//sum = sum == PLAYER_CELL ? 0 : sum;
	//printf("pc: %d\n", pc);
	//printf("piece sum2\n");
	return (pc == 1);
}
void	place_piece(t_filler *filler)
{
	int	i;
	int	j;
	int sum;
	int min_sum;
	//printf("place piece1\n");
	i = 0;
	min_sum = MAXINT;
	/*printf("ph: %d pw: %d\n", filler->piece->height, filler->piece->width);
	for (int k = 0; k < filler->piece->height; ++k) {
		for (int l = 0; l < filler->piece->width; ++l) {
			printf("%d ", filler->piece->map[k][l]);
		}
		printf("\n");
	}*/
	//printf("th: %d\n", filler->piece->th);
	while (filler->map->heat_map[i] && i <= filler->map->height - filler->piece->th)
	{

		j = 0;
		while (filler->map->heat_map[i][j] && j <= filler->map->width - filler->piece->tw)
		{
			if (is_fit(filler, j, i))
			{
				sum = calc_piece_sum(filler, j, i);
				if (sum >= 0 && sum < min_sum)
				{
					filler->x = j - filler->piece->x_top_left;
					filler->y = i - filler->piece->y_top_left;
					min_sum = sum;
				}
			}
			j++;
		}
		i++;
	}
	//printf("place piece2\n");

}
