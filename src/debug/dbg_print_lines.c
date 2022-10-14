/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dbg_print_lines.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 21:48:58 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/14 21:49:34 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

void	dbg_print_lines(char **lines)
{
	int	iter;

	iter = 0;
	while (lines[iter])
	{
		printf("%d: %s\n", iter, lines[iter]);
		iter++;
	}
}
