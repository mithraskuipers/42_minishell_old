#include "../includes/minishell.h"

void	tokens_add_types(t_list *tokenlist)
{
	t_token	*curr;

	if (!(tokenlist))
		return ;
	while (tokenlist)
	{
		curr = tokenlist->content;
		curr->type = tkn_str;
		if (curr->val[0] == '<')
			curr->type = tkn_read;
		if (curr->val[0] == '>')
			curr->type = tkn_write;
		if (curr->val[0] == '|')
			curr->type = tkn_pipe;
		if (curr->val[0] == '<' && curr->val[1] == '<')
			curr->type = tkn_heredoc;
		if (curr->val[0] == '>' && curr->val[1] == '>')
			curr->type = tkn_append;	
		tokenlist = tokenlist->next;
	}
}

int	tokens_check_syntax(t_list *tokenlist)
{
	t_token	*current;
	t_token	*next;

	if ((((t_token *)tokenlist->content)->type == tkn_pipe) || \
	(((t_token *)ft_lstlast(tokenlist)->content)->type != tkn_str))
		return (1);
	if ((t_token *)tokenlist->next == NULL)
		return (0);
	while (tokenlist && tokenlist->next)
	{
		current = (t_token *)tokenlist->content;
		next = (t_token *)tokenlist->next->content;
		if (current->type == tkn_read && next->type != tkn_str)
				return(msg_ret_int("< was not followed by string\n", 1));
		if (current->type == tkn_write && next->type != tkn_str)
				return(msg_ret_int("> was not followed by string\n", 1));
		if (current->type == tkn_pipe && next->type == tkn_pipe)
				return(msg_ret_int("| was followed by |\n", 1));
		if (current->type == tkn_heredoc && next->type != tkn_str)
				return(msg_ret_int("<< was not followed by string\n", 1));
		if (current->type == tkn_append && next->type != tkn_str)
				return(msg_ret_int(">> was not followed by string\n", 1));
		tokenlist = tokenlist->next;
	}
	return (0);
}

int	tokens_populate_tokenlist(char **lines, t_list **tokens)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		tokens_make_and_add(lines[i], tokens);
		i++;
	}
	return (0);
}

int	tokens_make_and_add(char *token_array, t_list **tokens)
{
	t_token	*token_obj;
	t_list	*token_list_elem;

	if (!token_array || (ft_strlen(token_array) == 0))
		return (1);
	token_obj = malloc(sizeof(t_token));
	if (!token_obj)
		return (1);
	token_obj->val = ft_strdup(token_array);
	if (!token_obj->val)
		return (1);
	free (token_array);
	token_list_elem = ft_lstnew(token_obj);
	if (!token_list_elem)
		return (1);
	ft_lstadd_back(tokens, token_list_elem);
	return (0);
}