/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 23:15:47 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/18 18:56:53 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains functions that are part of the input parsing section.
It analyses the input string and expands variables if applicable. Next, the
expanded string will be used for the tokenization process, where the expanded
string will be cut into pieces (i.e. words) and chained together into a 
linked list (see ms->tokenlist in minishell.h).
*/

#include "../includes/minishell.h"

/*
line_expander_helper() pdates the line it receives on a specific location
idea is that it is run several times so it can update the line completely
it is run when another functions came across env var in the line
with the repeated ft_memcpy it iteratively builds the updated line with an
expanded var
*/
char	*line_expander_helper(char *line, int pos, t_env **env)
{
	char	*key;
	char	*val;
	char	*newline;
	key = ft_substr(line, pos + 1, ft_strpos_first_nonalpha(&line[pos + 1]));
	val = env_get_val(env, key);
	if (val == NULL)
		val = "";
	newline = malloc((ft_strlen(line) + ft_strlen(val) + 1) * sizeof(char));
	ft_memcpy(newline, line, pos);
	ft_memcpy(&newline[pos], val, ft_strlen(val));
	ft_strcpy(&newline[pos + ft_strlen(val)], &line[pos + 1 + \
	ft_strpos_first_nonalpha(&line[pos + 1])]);
	free (key);
	free (line);
	return (newline);
}

/*
Loops over string until finds env var, replaces it, continues looping over string etc.
checks for single squote (squote) presence, because everything inside them needs to be
literal without expansion
*/

char	*line_expander(char *line, t_env **env)
{
	int	squote;
	int	i;

	i = 0;
	squote = 0;
	while (line[i])
	{
		if (squote == 0)
		{
			if (line[i] == '\'')
				squote = 1;
			if (line[i] == '$')
			{
				if (!(i - 3 >= 0 && line[i - 3] == '<' && line[i - 2] == '<'))
					line = line_expander_helper(line, i, env);
			}
		}
		else
			if (line[i] == '\'')
				squote = 0;
		i++;
	}
	return (line);
}