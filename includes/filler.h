#ifndef FILLER_H

# define FILLER_H
# define ERROR_CODE 0
# define OK_CODE 1
# define EMPTY_CELL  -1
# define PLAYER_CELL -2
# define ENEMY_CELL -3
# define MAXINT	2147483647

# include "../libft/libft.h"
# include "../libft/get_next_line.h"

typedef struct	s_map
{
	int			height;
	int			width;
	int			**heat_map;
}				t_map;

typedef struct s_piece
{
	char		**map;
	int			height;
	int 		width;
}				t_piece;

typedef struct s_filler
{
	t_map		*map;
	t_piece		*piece;
	char		player;
	char		enemy;
}				t_filler;

int				strsplit_len(char **str_arr);
int				validate_player(char **str);
void			strsplit_free(char **str_arr);
int				validate_map_head(char **str_arr);
int				validate_map_neck(char *str);
int				validate_map_body(char **str_arr);
int				error_gnl(char *str);
int				error_strsplit(char **str_arr);
int 			error_all(char *str, char **str_arr);
int				validate_piece_head(char **str_arr);
int				validate_piece_body(char *str);
int				init_heat_map(t_filler *filler);
int				error_piece(t_filler *filler);
t_filler		*init_filler();
int				parse_player(t_filler *filler);
int				parse_map(t_filler *filler);
int				parse_piece(t_filler *filler);
#endif