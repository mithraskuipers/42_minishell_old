/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:37 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/15 20:13:38 by mikuiper      ########   odam.nl         */
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
		tokenizer(ms); // segfault sometimes
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
