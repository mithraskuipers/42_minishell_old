/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   line_check_tools.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 14:55:32 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/21 11:14:01 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int line_check_quotations(char *line)
{
	int	quote;
	int	squote;

	quote = 0;
	squote = 0;
	while (*line)
	{
		if (*line == '\'' && squote == 0)
			squote = 1;
		else if (*line == '\'' && squote == 1)
			squote = 0;
		if (*line == '"' && quote == 0)
			quote = 1;
		else if (*line == '"' && quote == 1)
			quote = 0;
		line++;
	}
	if (quote || squote)
	{
		printf("Error. Your line has an unclosed quotation mark.\n");
		return (1);
	}
	return (0);
}

int	line_check_first_char(char *line)
{
	while (*line == ' ')
		line++;
	if (*line == '|')
	{
		printf("Error. Found forbidden token at start of line.\n");
		return (1);
	}
	return (0);
}

int	line_get_last_char(char *line)
{
	char	last_char;
	while (*line)
	{
		if (*line != ' ')
			last_char = *line;
		line++;
	}
	return (last_char);
}

int line_check_last_char(char *line, char *charset)
{
	if (*line && ft_strchr(charset, line_get_last_char(line)))
	{
		printf("Error. Found forbidden token at end of line.\n");
		return (1);
	}
	return (0);
}

int	line_check_syntax(char *line, char *charset)
{
	if (line_check_first_char(line))
		return (1);
	if (line_check_last_char(line, charset))
		return (1);
	if (line_check_quotations(line))
		return (1);
	return (0);
}