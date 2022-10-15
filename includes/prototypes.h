/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prototypes.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 13:35:21 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/15 19:17:43 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H
# include "structs.h"

/* SPLASH.C */
void	splash();
void	clear_screen(void);

/* INIT.C */
int		init_env_struct(t_ms *ms, char **envp);
int		init_start(void);

/* MAIN.C */
int		prompt(t_ms *ms);

/* EXPANDER.C */
char	*line_expander(char *line, t_env **env);
char	*line_insert_var(char *line, int pos, t_env **env);
int		line_dollar_presence(char *line);

/* ENV */
/* ENV_TO_ARRAYS.C */
char	**env_to_arrays(t_env **env);
char	**env_vals_to_arrays(t_env **env);
char	**env_entries_to_arrays(t_env **env);

/* ENV_ADD_VAR.C */
t_env	*env_create_var(char *key, char *val);
int		env_add_var(t_ms *ms, t_env *node);

/* ENV_TOOLS.C */
int		env_len(t_env **env);
int		env_get_var_key_idx(t_env **env, char *key);
char	*env_get_val(t_env **env, char *key);
int		env_init_idx(t_env **env);
int		env_edit_var_val(t_env **env, char *key, char *new_val);
int		env_key_exist(t_env **env, char *key);

/* ENV_CLONE_ENV */
int	env_var_cloner(t_ms *ms, char *line);

/* ENV_DELETE_VAR */
int		free_env_var(t_env *node);
int		env_del_var_helper(t_env **head, char *key);
int		env_del_var(t_env **env, char *key);

/* ERROR.C */
int		msg_ret_int(char *s, int ret);
void	*msg_ret_null(char *s);

/* EXEC.C */
int		execute_command(t_cmd *cmd);

// EXEC_LIST.C
t_exec_element	*exec_list_generator(t_exec_element *exec, int n_blocks, t_env **env);

/* PARSER */
/* LINE_PARSER.C */
int		line_parser(t_ms *ms);

/* LINE_SPLIT_INTO_LINES.C */
size_t	line_get_n_words(char *line);
size_t	line_get_line_len(char *line, size_t i);
char	**line_splitter_helper(char **lines, char *line);
char	**lines_trimmer(char **lines);
char	**line_splitter(char *line);

/* LINE_CHECK_TOOLS */
int 	line_check_quotations(char *line);
int		line_check_first_char(char *line);
int		line_get_last_char(char *line);
int 	line_check_last_char(char *line, char *charset);
int		line_checker(char *line, char *charset);

/* CLEAN.C */
int		clean_tokenlist(t_list **tokenlist);
int		clean_env(t_env **env);

/* BUILTINS */
/* ENV.C */
void	builtin_env(t_ms *ms, int fd);
int		builtin_pwd(int fd);
void	builtin_unset(t_ms *ms, char **args);
void	builtin_echo(t_cmd *cmd_object, int fd, int i);
int		builtin_export(t_ms *ms, t_cmd *cmd_object, int fd);
int	builtin_cd(t_cmd *cmd_object, t_ms *ms);
int	builtin_cd2(char **args, t_ms *ms); // just for testing, couldnt get builtin_cd to work for struct objects

/* EXE_BUILTIN.C */
int		exe_builtin(t_cmd *element, t_ms *ms);

/* tokens_populate_tokenlist.C */
int		tokens_check_syntax(t_list *tokenlist);
void	tokens_add_types(t_list *tokenlist);

/* MAKE_TOKENLIST */
int		tokens_make_and_add(char *token, t_list **tokens);
//int		tokens_populate_tokenlist(char *line, t_list **tokens);
int		tokens_populate_tokenlist(char **lines, t_list **tokens);
int		tokens_get_pipe_blk_len(t_list *tokenlist);
t_list	*make_token_blks_list(t_list **tokenlist);
char	**get_tokens_array(t_list *tokenlist);
int		tokens_make_and_add_token_blk(t_list **pipe_blk_list, char **token_array);

/* PIPE_BLK.C */
t_cmd		*cmd_constructor(char *prog_n, t_env **env);
void		cmd_deallocator(t_cmd *cmd);

/* PATH.C */
char	*get_path(char *prog_n, t_env **env);
int		free_ptr_array(char *ptr[]);


// DEBUG SECTION
void	dbg_print_lines(char **lines);
int		dbg_print_env(t_ms *ms);
int		dbg_print_env_idx(t_ms *ms);
int		dbg_print_env_keys(t_ms *ms);
int		dbg_print_tokens_val(t_list **tokenlist);
int		dbg_print_tokens(t_list **tokenlist);
int		dbg_print_token_blks_list(t_list *token_blks_list);

// TOKENS
t_exec_element	*tokenizer(t_ms *shell);

/* CHECKS.C */
// ERROR
int			check_fd(void);
//int			malloc_check(void *mem_loc);


/* COLORS.C */
void	color_red();
void	color_orange();
void	color_green();
void	color_reset();

#endif
