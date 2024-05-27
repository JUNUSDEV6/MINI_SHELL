/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:04:56 by clegros           #+#    #+#             */
/*   Updated: 2024/05/23 16:21:37 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	minishell_loop(char *line, char **envp)
{
    t_lexer         *lexer_list;
    t_simple_cmds   *cmd_list;
	char	        *args;

    cmd_list = malloc(sizeof(t_simple_cmds));
	(void)envp;
    lexer_list = NULL;
    cmd_list = NULL;
    //cmd_list->next = NULL;
    //current_cmd = NULL;
//	signal(SIGCHLD, SIG_IGN);
	while (1)
	{
		ft_set_input_signals();
		line = readline("minishell>> ");
		if (!line)
			break ;
		add_history(line);
        args = line;

        //-------------LEXER------------//
        tokenize(args, &lexer_list);
        print_list(lexer_list);

        //-------------PARSER-----------//
        convert_lexer_to_cmds(&lexer_list, &cmd_list);

        //--------------EXEC------------//
       // if (cmd_list)
       //     current_cmd = cmd_list;
        if (cmd_list)
        {
            if (cmd_list->str)
            {
                printf("a---\n");
                command_executer(cmd_list->str, envp, cmd_list);
            }
        }
        while (cmd_list != NULL)
        {
            printf("\n\nCommand:\n");
            int i = 0;
            while (cmd_list->str[i] != NULL)
            {
                printf("  %s\n", cmd_list->str[i]);
                i++;
            }
            printf("\n\nRedirections:\n");
            t_lexer *redir = cmd_list->redirections;
            while (redir != NULL)
            {
                printf("  %s\n", redir->token);
                redir = redir->next;
            }
            cmd_list = cmd_list->next;
        }
        
        //free_list(lexer_list);
        //free_cmds(cmd_list);


		/*while (list)
		{
			printf("f0ff----%s----|----%d----|----%s----\n", list->str, list->i, list->chr);
			list = list->next;
		}*/
		//free(list);
		//free(line);
		//free(args);
		args = NULL;
		line = NULL;
//		if (strcmp(list.cmd, "exit") == 0)
//			break ;
//		system("leaks ./minishell");
	}
}
int	main(int argc, char *argv[], char *envp[])
{
	char	*line;

	(void)argc;
	(void)argv;
	line = malloc(sizeof(char *));
	line = NULL;
	//signal_handler2(SIGINT);
	minishell_loop(line, envp);
}

//----------------ANCIEN_MAIN-----------------//

/*int main() {
    char input[] = "echo 'hello world' > g.txt | cat < g.txt << u.txt | grep > all >> yeah";
    t_lexer *lexer_list = NULL;

    tokenize(input, &lexer_list);
    print_list(lexer_list);

    t_simple_cmds *cmd_list = NULL;
    convert_lexer_to_cmds(&lexer_list, &cmd_list);

    t_simple_cmds *current_cmd = cmd_list;
    while (current_cmd != NULL)
    {
        printf("Command:\n");
        int i = 0;
        while (current_cmd->str[i] != NULL)
        {
            printf("  %s\n", current_cmd->str[i]);
            i++;
        }
        printf("Redirections:\n");
        t_lexer *redir = current_cmd->redirections;
        while (redir != NULL)
        {
            printf("  %s\n", redir->token);
            redir = redir->next;
        }
        current_cmd = current_cmd->next;
    }

    free_list(lexer_list);
    free_cmds(cmd_list);

    return 0;
}
*/
