/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:17:26 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/07 12:36:32 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
// please don't move this. It needs to be here. Otherwise it wont build on linux.
# include <stdlib.h> // getenv
# include <string.h>
/* #include <sys/syslimits.h>*/
# include <limits.h>       // this should work in linux
# include <linux/limits.h> // need it for PATH_MAX in linux
# include <sys/wait.h>     // for linux
# include <unistd.h>

# define IN 0
# define OUT 1

typedef struct s_node
{
	char			**full_cmd;
	int				pid;
	int				infile;
	int				outfile;
	struct s_node	*next;
}					t_node;

typedef struct s_env
{
	char			*key;
	char			*value;
}					t_env;

enum				e_builtins
{
	NONE,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};

// exec
t_node				*ft_parse_args(char *line, t_vec env);
int					ft_child(t_node *node, t_vec envv);
int					ft_executor(t_node *node, t_vec envv);
int					builtin_commands(char **cmd, t_vec envv);

// Env
int					ft_putenv(t_vec *envs_vec, char *str);
int					ft_putenv_key(t_vec *envs_vec, char *key, char *str);
char				*ft_getenv(t_vec envs_vec, char *key);
t_vec				ft_copyenv(char *env[]);
char				**ft_strenv(t_vec envs_vec);

// Parsing
char				**ft_cmd_trim(char *line);
void				ft_expand(t_vec vars, char **line);
char				**ft_split_operators(char **array);
char				**ft_str_trim(char **array);
// expand

void				ft_expand(t_vec env_vars, char **arr);
// char			*ft_var_end(char *str);
// char			*ft_var_expand(t_vec env_vars, char *str);
char				*ft_expand_token(t_vec env_vars, char *str);

// expand utils
// void			ft_tmp_to_result(char **result, char **tmp);
// int				ft_should_expand_tilde(char *token, char *token_init);

// split_operators

char				**ft_split_operators(char **array);
char				**ft_str_trim(char **array);

// cmd_trim
char				*allocate_token(char *token_start, char *token_end);
int					find_closing_quote(char *quote, int *closing_quote,
						char **line);
void				handle_quotes(char **line);
char				*next_token_from_line(char **line);
int					cmd_trim_len(char *line);

// split_operators
char				**divide_into_array(char **array, char **answer);
char				*no_operator(char *array);
char				*malloc_new_token(char **array);
int					get_next_token(char **string);
int					check_operators_num_in_string(char *array);
int					split_operators_len(char **array);
int					is_token_an_operator(char **str);

// str_trim
char				*check_for_trim(char *str);
int					is_trim_needed(char *str);
char				*trim_token(char *str, char *answer, int i, char quote);
int					token_is_double_quotes(char *str);

// fd_handler
t_node				*ft_fd_handler(char **array, t_node *node,
						int *error_here_docs, int node_counter);
void				find_and_open_fds(char **array);
int					here_doc(char *delimiter);
int					here_doc_invalid_infile(char **array, int i,
						int **error_here_docs, int node_counter);
int					reopen_file_and_check(char *name);
int					get_infile_fd(char **array, int error_here_doc,
						char *infile);
int					get_outfile_fd(char **array, char *outfile);
char				*find_last_infile(char **array);
char				*find_last_outfile(char **array);
int	check_for_invalid_file_before_infile(char **array,
											int **error_here_docs,
											int node_counter);

// exec_path
/**
 * @brief takes the cmd, checks through all the env which is the correct path
 * and finds the full path of the executable using the access function. 
 * @note   
 * @param  env t_vec pointer.
 * @param  cmd string.
 * @retval returns the full path of the cmd.
 */
char				*ft_get_exec_path(t_vec env, char *cmd);

// utils
// int				ft_max(int a, int b);
/**
 * @brief  Adds the path and the cmd together. 
 * @note   subfunction of ft_get_exec_path
 * @param  path string. 
 * @param  cmd	string.
 * @retval returns them joined. 
 */
static char			*ft_full_path(char *path, char *cmd);
/**
 * @brief  Uses perror for errno error message and exits.
 * @note   
 * @param  error_msg string for perror 
 * @retval None
 */
void				ft_pexit(char *error_msg);
/**
 * @brief  Checks if the command is a builtin.
 * @note echo = 1, cd 2, pwd 3, export 4, unset 5, env 6, exit 7.
 * @param  cmd string.
 * @retval 0 if not a builtin, the number associated if is.
 */
int					is_builtin(char *cmd);

// node funtions
/**
 * @brief  Creates all the nodes recursively, adds full_cmd, infile, outfile,
	and node.next.
 * @note  pid is added later when forked
 * @param  array Takes a pointer to a 2D array so it could be changed. 
 * @param  env vector environment for get_exact_path 
 * @param  error_here_docs int pointer array for here_docs if invalid infile.
 * @param  node_counter: keeps counter of the node to know which here_doc 
 * is associated with each node.
 * @retval The Head of the node list. 
 */
t_node				*new_node(char ***array, t_vec env, int *error_here_docs,
						int node_counter);
/**
 * @brief  Gets the node full_cmd.
 * @note   new_node subfunction.
 * @param  array Takes a pointer to a 2D array so it could be changed.
 * @retval returns the full_cmd of the current node.
 */
char				**get_node_cmd(char ***array);
/**
	* @brief  Checks if the current arguemnts until the pipe have
	any cmds that are not redirections.
 * @note  get_node_cmd subfunction. EXAMPLES < infile > outfile
	- returns 0. echo hi returns - 2
 * @param  array 2D string array.
 * @retval number of cmds 
 */
int					cmd_len(char **array);
/**
 * @brief Case of having only redirections without any executables.  
 * @note get_node_cmd subfunction. EXAMPLE : < infile > outfile  
 * @param  array Takes a pointer to a 2D array so it could be changed.
 * @retval None
 */
void				case_only_redirections(char ***array);
/**
	* @brief Case of having an empthy token after parsing. Moves the pointer to be NULL. 
	* @note get_node_cmd subfunction. EXAMPLE : $asdas becomes an empthy token after parsing. 
 * @param  array Takes a pointer to a 2D array so it could be changed.
 * @retval None
 */
void				case_empty_cmd(char ***array);
/**
 * @brief loops through the nodes and frees them. 
 * @note   
 * @param  node t_node pointer. node list head. 
 * @retval None
 */
void				free_nodes(t_node *node);

// piper
/**
	* @brief Creates 2D int array of allocated pipes. Loops through the nodes and changes the infile and outfile to be the IN end and OUT end of the pipe if needed.
 * @note   
 * @param  array string 
 * @param  node t_node pointer. node list head. 
 * @retval 2D int array with allocated pipes.
 */
int					**piper(char *array, t_node *node);
/**
 * @brief Allocates 2D int array for the number of pipes needed. 
 * @note piper subfunction.  
 * @param  array string
 * @retval 2D int array
 */
int					**allocate_pipes(char *array);
/**
 * @brief goes through the string and checks how many pipes there are.
 * @note  piper subfunction. 
 * @param  array string
 * @retval returns number of pipes (len) for memory allocation.
 */
int					num_of_pipes(char *array);
/**
	* @brief Loops through the nodes and checks if a pipe is needed for the processes,
	if it does it changes the infile and outfile to the in end and out end of the pipe. 
 * @note piper subfunction. IN OUT macros for read and write ends of the pipe.
 * @param  node t_node pointer. node list head.
 * @param  pipe_nbr 2D int array
 * @retval None
 */
void	change_infile_outfile_to_pipes(t_node *node,
									int **pipe_nbr);
/**
 * @brief Frees the allocated pipes. 
 * @note  piper subfunction. 
 * @param  pipe_nbr 2D int array. 
 * @param  array string 
 * @retval None
 */
void				free_pipes(int **pipe_nbr, char *array);

// Builtinså

/**
 * @brief  prints the arguments on the screen. 
 * @note option -n prints without newline. no args prints only newline.
 * @param  full_cmd 2D array. 
 * @retval None
 */
void				ft_echo(char **full_cmd);
/**
 * @brief  Exits the program when called
 * @note Exits the process if used with pipes
 * @retval None
 */
void				ft_exit(void);
/**
 * @brief prints the current path when called
 * @note   
 * @retval None
 */
void				ft_pwd(void);
/**
 * @brief  Gets the current full path
 * @note  Subfunction of ft_pwd & ft_cd
 * @retval string of the current path
 */
char				*get_path(void);
/**
 * @brief changing directories with only a relative or absolute path
 * @note   
 * @param  full_cmd 2D array.  
 * @param  envs t_vec pointer.
 * @retval None
 */
void				ft_cd(char **full_cmd, t_vec *envs);
/**
 * @brief prints the environment.
 * @note   
 * @param  envs t_vec pointer. 
 * @retval None
 */
void				ft_env(t_vec envs);
/**
 * @brief  adds a variable to the environment
 * @note   EXAMPLE : TEEMU=king
 * @param  full_cmd  2D array 
 * @param  envs t_vec pointer.
 * @retval None
 */
void				ft_export(char **full_cmd, t_vec *envs);
/**
 * @brief prints the declare list when export is called with no arguments
 * @note  subfunction of ft_export
 * @param  envs t_vec pointer.
 * @retval None
 */
void				export_no_arg(t_vec *envs);
/**
 * @brief Takes the variable and deletes it from the environment
 * @note  EXAMPLE : unset TEEMU=king
 * @param  envs t_vec pointer.
 * @param  key char pointer - string.
 * @retval None
 */
void				ft_unset(t_vec *envs, char *key);

#endif
