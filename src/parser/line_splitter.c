/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   line_splitter.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 11:14:12 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/15 19:17:33 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	line_get_n_words(char *line)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 1;
	while (line[i])
	{
		if (line[i] && line[i] == '\'' && line[i + 1])
		{
			while (line[++i] && line[i] != '\'')
				continue ;
		}
		else if (line[i] == '\"' && line[i + 1])
		{
			while (line[++i] && line[i] != '\"')
				continue ;
		}
		else if (line[i] && line[i] == '|')
			words++;
		i++;
	}
	return (words);
}

size_t	line_get_line_len(char *line, size_t i)
{
	size_t	len;

	len = 0;
	while (line[i + len])
	{
		if ((line[i + len]) && (line[i + len] == '\'') && (line[len + 1]))
		{
			len++;
			while ((line[i + len]) && (line[i + len] != '\''))
				len++;
		}
		else if ((line[i + len] == '\"') && (line[len + 1]))
		{
			len++;
			while ((line[i + len]) && (line[i + len] != '\"'))
				len++;
		}
		else if ((line[i + len]) && line[i + len] == '|')
			return (len);
		len++;
	}
	return (len);
}

char	**line_splitter_helper(char **lines, char *line)
{
	size_t	i;
	size_t	j;
	size_t	start;
	size_t	n_words;

	i = 0;
	start = 0;
	n_words = line_get_n_words(line);
	while (i < n_words)
	{
		j = 0;
		lines[i] = malloc(sizeof(char) * (line_get_line_len(line, start) + 1));
		if (!lines[i])
		{
			msg_ret_int("line_splitter_helper()", FAILURE);
			return (0);
		}
		while (line[start + j] && (j < line_get_line_len(line, start)))
		{
			lines[i][j] = line[start + j];
			j++;
		}
		lines[i][j] = '\0';
		start = start + line_get_line_len(line, start) + 1;
		i++;
	}
	lines[i] = NULL;
	return (lines);
}

char	**lines_trimmer(char **lines)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (lines[i])
	{
		tmp = lines[i];
		lines[i] = ft_strtrim(lines[i], " \t\v\r\n\f");
		free(tmp);
		i++;
	}
	return (lines);
}

char	**line_splitter(char *line)
{
	char	**lines;

	if (!line)
	{
		msg_ret_int("line_splitter()", FAILURE);
		return (NULL);
	}
	lines = malloc ((line_get_n_words(line) + 1) * sizeof(char *));
	if (!lines)
	{
		msg_ret_int("line_splitter()", FAILURE);
		return (NULL);
	}
	lines = line_splitter_helper(lines, line);
	if (!lines)
	{
		msg_ret_int("line_splitter()", FAILURE);
		return (NULL);
	}
	return (lines);
}
