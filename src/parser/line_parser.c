/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   line_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/30 11:47:20 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/14 22:31:50 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	line_parser(t_ms *ms)
{
	if (line_checker(ms->line, "<>|"))
		return (1);
	ms->line = line_expander(ms->line, ms->env);
	ms->lines = line_splitter(ms->line);
	ms->lines = lines_trimmer(ms->lines);
	return (0);
}

//
/* Tokenize line */
//tokens_populate_tokenlist(lines, &ms->tokenlist);

/* IMPORTANT: Please keep the following 4 lines of code for now. First elem of list is NULL. */
//t_list *head;
//head = ms->tokenlist;
//ms->tokenlist = ms->tokenlist->next;
//free (head);


/* Add labels to tokens */
//tokens_add_types(ms->tokenlist);

/* Check for valid token syntax */
//tokens_check_syntax(ms->tokenlist);

/* Demonstrate token blks */
//t_list	*token_blks_list;
//token_blks_list = make_token_blks_list(&ms->tokenlist);
//dbg_print_token_blks_list(token_blks_list);
