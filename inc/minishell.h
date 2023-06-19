/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:17:26 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/19 13:43:24 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <termios.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h> // this should be enough
# include <sys/wait.h> // for linux
# include <unistd.h>
# include <signal.h>
# include <sys/ioctl.h>

# define IN 0
# define OUT 1
# define REDIRECTION_NO_FILE -5

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
	FT_NONE,
	FT_ECHO,
	FT_CD,
	FT_PWD,
	FT_EXPORT,
	FT_UNSET,
	FT_ENV,
	FT_EXIT
};

// Env
/**
 * @brief Adds env string to envs_vec
 *
 * @param envs_vec
 * @param str
 * @return int
 */
int					ft_putenv(t_vec *envs_vec, char *str);
/**
 * @brief Adds str tp envs_vec based on the key
 *
 * @param envs_vec
 * @param key
 * @param str
 * @return int
 */
int					ft_putenv_key(t_vec *envs_vec, char *key, char *str);
/**
 * @brief Gets env value
 *
 * @param envs_vec
 * @param key
 * @return char*
 */
char				*ft_getenv(t_vec envs_vec, char *key);
/**
 * @brief Copies the given environment variables to to envs_vec
 *
 * @param env
 * @return t_vec
 */
t_vec				ft_copyenv(char *env[]);
/**
 * @brief Turns envs_vec to string array
 *
 * @param envs_vec
 * @return char**
 */
char				**ft_strenv(t_vec envs_vec);

// Expand

void				ft_expand(t_vec env_vars, char **arr);
char				*ft_expand_token(t_vec env_vars, char *str);

// Signals
void				sig_ctrl_c(int signal);
void				sig_ctrl_c_exec(int signal);

// PARSE ARGS
/**
 * @brief parses the line and sets each node to have the information
 * needed for each proccess.
 * @note
 * @param  line string. line from user.
 * @param  env t_vec.
 * @retval The head node of the node list.
 */
t_node				*ft_parse_args(char *line, t_vec env);
/**
 * @brief Changes the STDIN & STDOUT of the process to be the infile and outfile.
 * executes the commands using execve.
 * @note if execve is successful the whole process is overwritten.
 * @param  node pointer to t_node.
 * @param  envv t_ved
 * @retval 0
 */
int					ft_child(t_node *node, t_vec envv);
/**
 * @brief loops through the nodes, forks and enters child processes.
 * @note  exits if fork fails.
 * @param  node pointer to t_node. Head of list.
 * @param  envv t_ved
 * @retval returns 0.
 */
int					ft_executor(t_node *node, t_vec envv);
/**
 * @brief If the command if one of the builtins we call the specific one.
 * @note
 * @param  cmd 2D array
 * @param  envv t_vec
 * @retval Exits the process after executing the command.
 */
int					builtin_commands(char **cmd, t_vec envv);

// cmd_trim
/**
 * @brief Takes the line and seperates it to tokens.
 * @note
 * @param  line string.
 * @retval 2D array of tokens.
 */
char				**ft_cmd_trim(char *line);
/**
 * @brief Allocates and copies the token.
 * @note  subfunction of ft_cmd_trim.
 * @param  token_start pointer to beggining of the token.
 * @param  token_end pointer to the end of the token.
 * @retval New allocated token.
 */
char				*allocate_token(char *token_start, char *token_end);
/**
 * @brief Finds the closing quote and moves the pointer to there.
 * changes the value of closing_quote if found to 1.
 * changes quote to 0 if found attached double quotes.
 * @note  subfunction of ft_cmd_trim.
 * @param  quote pointer to char
 * @param  closing_quote pointer to char
 * @param  line pointer to string.
 * @retval 1 if found the closing quote, 0 if not.
 */
int					find_closing_quote(char *quote, int *closing_quote,
						char **line);
/**
 * @brief Handles the case of a token with quotes.
 * moves the pointer to the end of the closing quote.
 * EXAMPLE "somthing this that" - this is one token
 * @note  subfunction of ft_cmd_trim.
 * @param  line pointer to a string.
 * @retval None
 */
void				handle_quotes(char **line);
/**
 * @brief Gets the next token from the line, handles token
 * as multiple words under quotes. moves the pointer hence
 * changing the value of the string.
 * @note subfunction of ft_cmd_trim.
 * @param  line pointer to a string.
 * @retval returns the next token from the line allocated.
 */
char				*next_token_from_line(char **line);
/**
 * @brief Gets the number of tokens to be  allocated.
 * @note  subfunction of ft_cmd_trim.
 * @param  line string.
 * @retval number of tokens to be allocated.
 */
int					cmd_trim_len(char *line);

// split_operators
/**
 * @brief  Splits the tokens if there's operators attached together.
 * @note
 * @param  array 2D array.
 * @retval 2D array of tokens after being splited.
 */
char				**ft_split_operators(char **array);
/**
 * @brief Creates the new array of tokens after they're
 * splitted if they're together.
 * @note subfunction of ft_split_operators.
 * @param  array 2D array.
 * @param  answer 2D array.
 * @retval 2D array of tokens after being splited.
 */
char				**divide_into_array(char **array, char **answer);
/**
 * @brief returns malloced token if there is no operator inside.
 * @note  subfunction of ft_split_operators.
 * @param  array string.
 * @retval malloced token.
 */
char				*no_operator(char *array);
/**
 * @brief Gets the next token, mallocs it and returns it.
 * @note  subfunction of ft_split_operators.
 * @param  array pointer to a string.
 * @retval returns the token.
 */
char				*malloc_new_token(char **array);
/**
 * @brief Gets the next token by moving the pointer of the string.
 * EXAMPLE: "<Makefile|" first call - return 1, modified string "Makefile|".
 * second call - return 8, modified string "|".
 * third call - return 1, modified string "".
 * @note subfunction of ft_split_operators.
 * @param  string pointer to a string.
 * @retval the lenght of the token.
 */
int					get_next_token(char **string);
/**
 * @brief Checks if there is any operators in the string.
 * @note subfunction of ft_split_operators.
 * @param  array string.
 * @retval returns the number of operators. 0 if none.
 */
int					check_operators_num_in_string(char *array);
/**
 * @brief  Checks the lenght of the new 2D array after splitting the toekns.
 * Doing it by moving the pointer of the array token by token.
 * @note subfunction of ft_split_operators.
 * @param  array 2D string array.
 * @retval lenght of number of tokens for new array.
 */
int					split_operators_len(char **array);
/**
 * @brief Checks if the token is an operator and moves the pointer accordinly.
 * @note subfunction of ft_split_operators. chnages the value of str.
 * @param  str pointer to a string
 * @retval 2 if its <<  >>, 1 if its <  |  > and 0 if not.
 */
int					is_token_an_operator(char **str);

// str_trim
/**
 * @brief takes the tokens and trimmes them from any unnecessary quotes
 * @note
 * @param  array pointer to a string. so the value could be changed.
 * @brief takes the tokens and trims them from any unnecessary quotes
 * @note
 * @param  array pointer to a string. so the value could be changed.
 * @retval 2D array of tokens, trimmed if needed.
 */
char				**ft_str_trim(char **array);
/**
 * @brief Checks for edge cases, and trims the token if needed.
 * @note  subfunction of ft_str_trim
 * @param  str string.
 * @retval returns the token after checking trim, trims if needed.
 */
char				*check_for_trim(char *str);
/**
 * @brief  Checks if the token needs to be trimmed.
 * @note subfunction of ft_str_trim
 * @param  str string.
 * @retval if needed 1 returned, 0 if not.
 */
int					is_trim_needed(char *str);
/**
 * @brief Trims the token and returns it without the quotes
 * @note  subfunction of ft_str_trim
 * @param  str string.
 * @param  answer string.
 * @param  i index
 * @param  quote char - which quote to trim
 * @retval returns the trimmed token
 */
char				*trim_token(char *str, char *answer, int i, char quote);
/**
 * @brief Checks if the token is only double quotes
 * @note EXAMPLE : "" or ''. subfunction of ft_str_trim
 * @param  str string.
 * @retval returns 1 if it is, 0 if not.
 */
int					token_is_double_quotes(char *str);

// fd_handler
/**
 * @brief takes the current node and returns it with the infile
 * and outfile of the process
 * @note if pipes are needed piper function will change them later.
 * @param   array 2D string array.
 * @brief takes the current node and returns it with
 * the infile and outfile of the process
 * @note if pipes are needed piper function will change them later.
 * @param   array 2D string array.
 * @param  node t_node pointer.
 * @param  error_here_docs int array to keep here_docs if invalid file,
 * they need to be opened before the error message
 * @param  node_counter keeps counter of the node to know which here_doc
 * is associated with each node.
 * @retval The node after addidng the fd's.
 */
t_node				*ft_fd_handler(char **array, t_node *node,
						int *error_here_docs, int node_counter);
/**
 * @brief opens other fd's that are not infile or outfile
 * @note subfunction of ft_fd_handler. closes them after openning
 * @param  array 2D string array.
 * @retval None
 */
void				find_and_open_fds(char **array);
/**
 * @brief  Creates a here_doc and opens it.
 * @note
 * @param  delimiter string.
 * @retval returns the fd
 */
int					here_doc(char *delimiter);
/**
 * @brief opens and stores all the here_doc fd's
 * if there is an invalid file and all the here_docs
 * need to be opened before the error message
 * @note subfunction of check_for_invalid_file_before_infile
 * @param  array 2D string array.
 * @param  i int
 * @param  error_here_docs pointer to and int array
 * to change the values from the funtion
 * @param  node_counter keeps counter of the node to know which here_doc
 * is associated with each node.
 * @retval -1
 */
int					here_doc_invalid_infile(char **array, int i,
						int **error_here_docs, int node_counter);
/**
 * @brief  reopens the here_doc to reset the file "cursor" and checks if valid.
 * @note subfunction of here_doc
 * @param  name string, here_doc name
 * @retval fd if valid, -1 if not
 */
int					reset_cursor(char *name);
/**
 * @brief Opens the infile, crates a here_doc if that's the infile.
 * If there was an invalid infile in any other node and here_doc was already
 * created it gets it from error_here_doc
 * @note  subfunction of ft_fd_handler.
 * @param  array 2D string array.
 * @param  error_here_doc here_doc fd for associated node if there was invalid
 * file. If there was an invalid infile in any other node and here_doc
 * was already created it gets it from error_here_doc
 * @note  subfunction of ft_fd_handler.
 * @param  array 2D string array.
 * @param  error_here_doc here_doc fd for associated node if invalid file.
 * @param  infile string, last infile from find_last_infile
 * @retval fd of infile.
 */
int					get_infile_fd(char **array, int error_here_doc,
						char *infile);
/**
 * @brief  Creates the outfile and returns the fd.
 * @note   subfunction of ft_fd_handler.
 * @param  array 2D string array.
 * @param  outfile string, last outfile from find_last_outfile
 * @retval fd of outfile.
 */
int					get_outfile_fd(char **array, char *outfile);
/**
 * @brief  finds the last redirection which is the infile.
 * @note  subfunction of ft_fd_handler.
 * @param array 2D string array.
 * @retval returns infile.
 */
char				*find_last_infile(char **array);
/**
 * @brief  finds the last redirection which is the outfile.
 * @note subfunction of ft_fd_handler.
 * @param array 2D string array.
 * @retval returns outfile.
 */
char				*find_last_outfile(char **array);
/**
 * @brief Check if there is any invalid file before the infile or
 * if the infile is invalid and then opening all the here_docs before
 * the error.
 * @note subfunction of ft_fd_handler. uses the function
 * here_doc_invalid_infile to keep all the here_docs opened before the error
 * in error_here_docs int array.
 * @param  array 2D string array.
 * @param  error_here_docs a pointer to an int array so the value could
 * be changed.
 * @param  node_counter keeps counter of the node to know which here_doc
 * @brief Check if there is any invalid file before the infile
 * or if the infile is invalid and then opening all the here_docs
 * before the error.
 * @note subfunction of ft_fd_handler. uses the function
 * here_doc_invalid_infile to keep all the here_docs opened before
 * the error in error_here_docs int array.
 * @param  array 2D string array.
 * @param  error_here_docs a pointer to an int array so the value
 * could be changed.
 * @param  node_counter keeps counter of the node to know which here_doc
 * is associated with each node.
 * @retval -1 if invalid file 0 if not.
 */
int					check_for_invalid_file_before_infile(char **array,
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
char				*ft_full_path(char *path, char *cmd);
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
	any tokens that are not redirections.
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
	* @brief Case of having an empty token after parsing. Moves the pointer
	* to be NULL.
	* @note get_node_cmd subfunction. EXAMPLE : $asdas becomes an empthy token
	* after parsing.
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
 * @brief Creates 2D int array of allocated pipes. Loops through the nodes
 * and changes the infile and outfile to be the IN end and OUT end of
 * the pipe if needed.
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
 * @brief Loops through the nodes and checks if a pipe is needed for
 * the processes,
 * if it does it changes the infile and outfile to the in end and out end
 * of the pipe.
 * @note piper subfunction. IN OUT macros for read and write ends of the pipe.
 * @param  node t_node pointer. node list head.
 * @param  pipe_nbr 2D int array
 * @retval None
 */
void				change_infile_outfile_to_pipes(t_node *node,
						int **pipe_nbr);
/**
 * @brief Frees the allocated pipes.
 * @note  piper subfunction.
 * @param  pipe_nbr 2D int array.
 * @param  array string
 * @retval None
 */
void				free_pipes(int **pipe_nbr, char *array);

// Builtins

/**
 * @brief  prints the arguments on the screen.
 * @note option -n prints without newline. no args prints only newline.
 * @param  full_cmd 2D array.
 * @param outfile int
 * @retval None
 */
void				ft_echo(char **full_cmd, int outfile);
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

/**
 * @brief  welcome message to our shell
 * @note
 * @retval None
 */
void				welcome_message(void);
/**
 * @brief Loops through the node list and checks if any of them has infile
 * set as REDIRECTION_NO_FILE.
 * @note
 * @param  head t_node. Head of the list
 * @retval 1 if found in the list, 0 if not
 */
int					redirection_no_file_in_nodes(t_node *head);
/**
 * @brief Checks if the redirection has no file name.
 * @note
 * @param  array 2D string array
 * @retval 1 if it has no file name, 0 if everything is good
 */
int					check_for_redirection_no_file_name(char **array);

#endif
