#include "../../includes/minishell.h"

static int	ft_equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}
/*
static void	ft_del_quotes(t_simple_cmds *cmd)
{

}

static void	ft_check_param(t_simple_cmds *cmd, char **env_p)
{
	if (ft_equal_sign(cmd->str[1]) == 0)
		return (EXIT_FAILURE);
	
}

static void	ft_var_exist(t_simple_cmds *cmd, char **env_p)
{

}
*/
static char	**add_loop(char **envp, char **ret, char *var)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (envp[i + 1] == NULL)
		{
			ret[i] = ft_strdup(var);
			ret[i + 1] = ft_strdup(envp[i]);
		}
		else
			ret[i] = ft_strdup(envp[i]);
		if (ret[i] == NULL)
			return (ret);
		i++;
	}
	return (ret);
}
static char	**ft_add_var(char **envp, char *var)
{
	char	**ret;
	int		i;

	i = 0;
	if (var[ft_equal_sign(var)] == '\'')
		delete_quotes(var, '\'');
	if (var[ft_equal_sign(var)] == '\"')
		delete_quotes(var, '\"');
	while (envp[i] != NULL)
		i++;
	ret = ft_calloc(sizeof(char *), i + 2);
	i = 0;
	add_loop(envp, ret, var);
	return (ret);
}

int	ft_export(t_simple_cmds *cmd, char **env_p)
{
	int		i;
	char	**temp;

	i = 0;
	(void)cmd;
	(void)env_p;
	while (!cmd->str[i])
	{
		if (cmd->str[i])
		{
			temp = ft_add_var(env_p, cmd->str[i]);
			env_p = temp;
		}
		i++;
	}
	i = 0;
	//while (temp[0])
	printf("\n\n%s\n", temp[0]);
	return (EXIT_SUCCESS);
}