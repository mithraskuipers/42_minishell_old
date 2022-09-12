/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/26 16:25:57 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/10 18:06:01 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
#include <limits.h>
#include <unistd.h>
#include <stdio.h>

/*
NOTE:
_POSIX_PATH_MAX is used to maintain compatibility on
POSIX compatible systems. This ensures that the buffer size of pwd
is always large enough to hold the path.
*/

int	ms_pwd(void)
{
	char	pwd[_POSIX_PATH_MAX];

	if (getcwd(pwd, _POSIX_PATH_MAX) == NULL)
		return (1);
	printf("%s\n", pwd);
	return (0);
}
