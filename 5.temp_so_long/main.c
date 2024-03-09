#include "so_long.h"

/*Al main posso passare diverse mappe*/
int	main(int argc, char **argv)
{
	/*Static perche' */
	static t_game game;

	/*---------------------CONTROLLI INIZIALI ED INIZIALIZZAIONE-----------------*/
	if (argc != 2)
	{
		ft_printf("Error1: invalid number of parameters");
		return (1);
	}
	
	set_var_to_zero(&game);                       /*HO MESSO LA FUNZIONE PER ZERARE QUI, VEDERE SE NON DA PROBLEMI*/
	if (matrix_generator(&game, argv[1]) != 0)
	{
		print_matrix(&game);
		launch_game(&game);
	}

}