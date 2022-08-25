/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:37 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/25 13:53:39 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
sudo apt-get install libreadline-dev
*/

/*
env = ft_calloc(1, sizeof(t_env));
if (!env)
	exit(1);
*/

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	printf("\nSTART OF MINISHELL\n");	
	t_ms *ms;
	ms = ft_calloc(1, sizeof(t_ms));

	(void)argc;
	(void)argv;
	if (init_wrapper(ms, envp))
		return (1);
	(void)ms;
	printf("\nEND OF MINISHELL\n");	
	return 0;
}
