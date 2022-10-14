/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/29 18:24:05 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/14 22:35:11 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			msg_ret(char *s, int ret)
{
	printf("%s", s);
	return (ret);
}

void	*msg_null(char *s)
{
	printf("%s", s);
	return (NULL);
}

// Below is nonsense. But please do not yet delete it. Its silly usage
// can be hypothetically used to shorten a function thats >= 25 lines

/*
static void	ms_exit(char *msg, int exit_code)
{
	ft_putendl_fd(msg, 2);
	exit(exit_code);
}
*/

// int			malloc_check(void *mem_loc)
// {
// 	if (mem_loc == NULL)
// 		return (1);
// 	return (0);
// }
