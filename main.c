#include <stdio.h>
#include <stdlib.h>



typedef struct s_list
{
	int			x;
	int			y;
	int			z;
	struct s_list	*next;
}				t_list;