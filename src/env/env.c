/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 15:03:21 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/18 15:58:46 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
env_len() returns the number of nodes in the env linked list.
*/

int	env_len(t_env **env)
{
	int		i;
	t_env	*head;

	i = 0;
	head = *env;
	
	if (!head)
		return (0);
	else
	{
		while (head->next)
		{
			head = head->next;
			i++;
		}
		i++;
	}
	return (i);
}

/*
env_create_node() can be used to create a new node for the env linked list.
Following the creation, it can be added to the linked list using 
env_add_entry().
*/

t_env	*env_create_node(char *key, char *val)
{
	t_env	*node;

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (!node->key)
		return (NULL);
	node->val = ft_strdup(val);
	if (!node->val)
	{
		free (node->val);
		return (NULL);
	}
	node->idx = -1;
	node->next = NULL;
	return (node);
}

/*
env_get_key_idx() returns the index value of a desired key in the env linked
list. If the key does not exist, or if no linked list is provided, it returns -1.
*/

int	env_get_key_idx(t_env **env, char *key)
{
	t_env	*head;
	int		i;

	head = *env;
	i = 0;
	if (!head)
		return (-1);
	else
	{
		while (head->next)
		{
			if (ft_strlen(head->key) == ft_strlen(key))
				if (!ft_strncmp(head->key, key, ft_strlen(head->key)))
					return (head->idx);
			head = head->next;
			i++;
		}
	}
	return (-1);
}

/*
env_get_val() returns the value corresponding to a desired key in the env linked
list. If the key does not exist, or if no linked list is provided, it returns
NULL.
*/

char	*env_get_val(t_env **env, char *key)
{
	t_env	*head;
	int	i;

	if (strlen(key) == 0)
		return ("");
	head = *env;
	i = 0;
	if (!head || env_get_key_idx(env, key) == -1)
		return (NULL);
	else
	{
		while (head->next)
		{
			if (i == env_get_key_idx(env, key))
				return (head->val);
			head = head->next;
			i++;
		}
	}
	return (head->val);
	//return (NULL);
}

/*
env_init_idx() is used to assign index values to each node in the env linked
list.
*/

int	env_init_idx(t_env **env)
{
	int		i;
	t_env	*head;

	i = 0;
	head = *env;
	if (!head)
		return (1);
	else
	{
		while (head->next)
		{
			head->idx = i;
			head = head->next;
			i++;
		}
		i++;
		head->idx = i;
	}
	return (0);
}

/*
env_add_entry() adds a new node to the end of the env linked list. It is
repeatedly called by env_entry_cloner(), which creates a new node for each 
system env line.
*/

int	env_add_entry(t_ms *ms, t_env *node)
{
	t_env *cur;

	if (env_len(ms->env))
	{
		cur = *ms->env;
		while (cur->next)
			cur = cur->next;
		cur->next = node;
	}
	else
	{
		*ms->env = node;
	}
	return (0);
}

/*
env_entry_cloner() can be used to clone the system env into memory. The new env
is represented in a linked list, where each node contains the data of a single
line of the system env. Each node separates the data from a system env line into
key and value pairs.
*/

int	env_entry_cloner(t_ms *ms, char *line)
{
	t_env	*node;

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (1);
	node->key = ft_substr(line, 0, ft_strchr(line, '=') - line);
	if (!node->key)
	{
		return (1);
	}
	node->val = NULL;
	if (ft_strchr(line, '='))
	{
		node->val = ft_strdup(&ft_strchr((line), '=')[1]);
		if (node->val == NULL)
			return (1);
	}
	node->next = NULL;
	if (env_add_entry(ms, node))
		return (1);
	return (0);
}

/*
env_edit_val() allows for changing the value of a particular key in your env.
It does this by searching for the key in the linked list env, starting at the
head. Note: This function assumes that your env has no duplicate keys. If a
duplicate key exists, this function will only update the value of the first 
occurring key.
*/

int	env_edit_val(t_env **env, char *key, char *new_val)
{
	t_env	*head;
	int		i;

	head = *env;
	i = 0;
	if (!head)
		return (1);
	else
	{
		while (head->next)
		{
			if (!ft_strncmp(head->key, key, ft_strlen(key)))
			{
				free (head->val);
				head->val = ft_strdup(new_val);
				if (!head->val)
					return (1);
				return (0);
			}
			head = head->next;
			i++;
		}
	}
	return (1);
}

/*
free_env_node() frees the memory that was allocated per environment node.
It is used by env_del_entry_helper().
*/

int	free_env_node(t_env *node)
{
	free (node->key);
	free (node->val);
	free (node);
	return (0);
}

/*
env_del_entry_helper() is a helper function used by env_del_entry().
It merely exists to make env_del_entry() comply with the 42 norme.
*/

static int	env_del_entry_helper(t_env **head, char *key)
{
	t_env *current;
	t_env *next_node;
	t_env *next_next_node;

	current = *head;
	while(current->next != NULL)
	{
		next_node = current->next;
		if(next_node->idx == env_get_key_idx(head, key))
		{
			next_next_node = next_node->next;
			current->next = next_next_node;
			free_env_node(next_node);
			return (0);
		}
		else
			current = current->next;
	}
	return (0);
}

/*
env_del_entry() allows for the deletion of an environment entry by providing
the entry's corresponding key. If the key does not exist it returns 1, else 0.
*/

int	env_del_entry(t_env **env, char *key)
{
	t_env *next_node;
	
	if (env_get_key_idx(env, key) == -1)
		return (1);
	if((*env)->idx == env_get_key_idx(env, key))
	{
		next_node = *env;
		*env = (*env)->next;
		free_env_node(next_node);
	}
	else
		env_del_entry_helper(env, key);
	return (0);
}