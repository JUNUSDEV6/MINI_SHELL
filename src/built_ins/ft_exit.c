#include "../../includes/minishell.h"

int	ft_exit(t_simple_cmds *cmd)
{
	(void)cmd;
	printf("-_-\n");
	exit(EXIT_FAILURE);
	return (EXIT_FAILURE);
}