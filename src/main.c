/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:37 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/16 11:37:01 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int global_error;

// emptied for clarity for what is called in main()
int	prompt(t_ms *ms)
{
	(void)ms;
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_ms *ms;

	global_error = 1;

	if (argc == 1 && argv)
	{
		if (check_fd())
			return (msg_ret_int("fd problem()", FAILURE));
		ms = ft_calloc(1, sizeof(t_ms));
		if (!ms)
			return (1);
		ms->line = NULL;
		if (init_env_struct(ms, envp))
			return (msg_ret_int("init_env_struct()", FAILURE));
		prompt(ms);
		splash();
		ms->line = readline("λ :: > ");
		line_parser(ms);
		ms->cmds_new = ft_calloc(ft_get_n_strings(ms->lines), sizeof(t_cmds_new));
		if (!ms->cmds_new)
		{
			// if fails, cleanup everything
			return (1);
		}
		size_t i = 0;
		while (i < ft_get_n_strings(ms->lines))
		{
			ms->cmds_new[i].cmd = NULL;
			ms->cmds_new[i].path = NULL;
			ms->cmds_new[i].fd_in = 0;
			ms->cmds_new[i].fd_out = 1;
			i++;
		}
		
		//tokenizer(ms); // segfault sometimes
		// TOKENIZER
		// TOKENIZER CLEANUP (QUOTATIONS)
	
		//dbg_print_lines(ms->lines);
		//clean_tokenlist(&ms->tokenlist);
		//clean_env(ms->env);
		//free (ms);
		return (0);
	}
	return (msg_ret_int("Please do not provide any arguments.", 1));
}
