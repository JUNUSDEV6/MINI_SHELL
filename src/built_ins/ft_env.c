#include "../../includes/minishell.h"

int	ft_env(t_simple_cmds *cmd, char **env_p)
{
	(void)cmd;
	int	i;

	i = 0;
	while(env_p[i])
	{
		printf("-%s\n", env_p[i++]);
	}
	return (0);
}