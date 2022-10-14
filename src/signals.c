/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 23:08:30 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/14 23:09:45 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

// used to update signal value whenever

void	sig_int(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	ft_putchar_fd('\n', STDERR_FILENO);
	rl_on_new_line();
	rl_redisplay();
	global_error = 1;
}
