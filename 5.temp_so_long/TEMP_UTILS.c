#include "so_long.h"

/****************************************************************/

void	print_matrix(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->map.heigth)
		ft_printf("%s\n", game->matrix[i]);
}