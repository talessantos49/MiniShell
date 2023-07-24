/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:52:02 by root              #+#    #+#             */
/*   Updated: 2023/07/24 13:50:50 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdarg.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/uio.h>

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/libft/libft.h"

# define SPACES " \t\r\f\v"
# define COLOR "\033[1;35m"
# define HDSIGQUIT1 "\nminishell: warning: here-document delimited by \
end-of-file (wanted `"
# define HDSIGQUIT2 "')\n"
# define SPECIALS "<>|"
# define QUOTES "\'\""
# define HEREDOCNAME ".tmp00"
# define GLOBAL 0
# define LOCAL 1
# define ENVP 2
# define ERR_ARG "minishell: too many arguments"
# define NO_FREE 0
# define FREE_SHELL 0
# define ONLYSIGQUIT 1
# define ONLYSIGINT 2
# define SIGQUIT_SIGINT 3
# define ERRORFLAG1 "bash: %s: -%c: invalid option\n"
# define ERRORFLAG2 "%s: invalid option -- '%c'\n"

extern int			g_signal;

typedef struct s_cmd
{
	char			quote;
	int				flag;
	char			*arg;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	char			*var;
	char			*msg;
	int				type;
	int				len_var;
	int				len_msg;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct s_block
{
	char			*heredoc_name;
	char			*current_var;
	char			**args;
	char			*cmd;
	char			quote;
	int				*quote_position;
	int				commands_n;
	int				fd[2];
	int				pipe[2];
	int				set;
	int				signal;
	t_cmd			*commands;
	t_cmd			*current_command;
	struct s_block	*next;
	void			(*built_in)(void *shell);
}					t_block;

typedef struct s_shell
{
	char		**env_mtx;
	char		**paths_mtx;
	char		*line;
	char		*heredoc_name;
	char		*actual_path;
	int			exit_code;
	int			count;
	int			env_n;
	int			paths_n;
	int			pipelist_n;
	int			status;
	int			std_io[2];
	pid_t		pid;
	t_block		*pipelist;
	t_env		*env;
}				t_shell;

// base
// char	*make_text(void);
char	*make_text(t_shell **shell);
void	minishell(t_shell **shell);
void	execution(t_shell **shell, t_block *current);
void	free_pipe_list(t_shell **shell, t_block *current);
void	perror_free(char *type, char *name);
void	safe_free(void **ptr);
// Split
char	**split_commands(t_shell **shell, char *s, char c);
// Pipe_List
t_block	*new_block_on_pipe_list(t_shell **shell, t_block *block_current);
// Built-in's
int		find(char *string1, char c);
int		strcmp_mod(const char *s1, const char *s2);
void	c_cd(t_shell **shell);
void	c_echo(t_shell **shell);
// char	*process_text(t_shell **shell);
void	c_env(t_shell **shell);
void	c_exit(t_shell **shell);
void	c_export(t_shell **shell);
// void	c_pwd(t_shell **shell);
void	c_pwd(void);
void	c_unset(t_shell **shell);
void	c_clear(void);
void	*is_built_in(char *command);
void	restore_std_io(int *std_io);
char	*strchr_rev(const char *str, int c);
int		strcmp_mod(const char *s1, const char *s2);
char	*strchr_mod(const char *str, int c);
char	*strchr_rev(const char *str, int c);
int		ft_isalnum_mod(int c);
void	apart_args(t_shell **shell, char c, void (*function)());
int		builtin_setup(t_shell **shell, char **args);
void	error(char *msg, t_shell **shell, int free_type, int exit_code);
void	heredoc_name_setup(t_shell **shell, t_block *current);
// void	here_doc_exec(t_block *current, char *delimiter, int mode);
void	here_doc_exec(t_block *current, char *delimiter);
char	*here_doc_setup(t_shell **shell, t_block *current, char *line);
t_env	*make_list(t_shell **shell, char **envp);
void	handle_sigquit(t_shell **shell);
void	handle_sigint(int signal);
void	signal_listener(__sighandler_t handle_quit, __sighandler_t handle_int);
void	signals_line(t_shell **shell);
void	signal_set(int signal);
char	*is_spaces(char *line, char *spaces);
char	*is_no_word(t_shell **shell, t_block *current, char *line);
void	free_shell(t_shell **shell);
// args
int		is_flag_null(t_shell **shell, char *pattern);
void	print_flag_error(char *command, char *flag, int flag_len, int cmd_len);
void	is_enviroment_definition(t_shell **shell, char *line, int i, int k);
void	add_node(t_env **list, t_env *node);
char	*change_enviroment(t_shell **shell, char *line, int i, int k);
t_env	*node_atribuition(char *var, char *msg);
void	replace_word(char *string, const char *wordToReplace,
			const char *replacement, int offset);
t_env	*find_arg(t_shell **shell, char *var);
void	signal_handled_exec(t_shell **shell);
//ordenated later;
void	quote_clean(t_block *current, char *command, char quote);
char	*quote_unclosed(t_block *current, char *input);
int		is_quote(t_block *current, char line);
void	new_command(t_block *current);
char	*is_command(t_shell **shell, t_block *current, char *line);
char	*is_file_io(t_shell **shell, t_block *current, char *line);
char	*is_special(t_shell **shell,
			t_block *current, char *line, char *specials);
void	manage_file_descriptors(t_block *current, char *file_name);
char	*special_cases(t_shell **shell, t_block *current, char *line);
void	args_matrix(t_block *current);
void	pipe_list_build(t_shell **shell, char *line);
void	needs_env_update(t_shell **shell, t_env *current, int env_n);
int		is_var(t_shell **shell, char *var);
void	remove_variable(t_shell **shell, t_env **list, char *var);
char	*ft_strip(char *line, char striped_char);
void	c_var_definition(t_shell **shell);
void	change_var(t_shell **shell, char *var, char *msg);
char	*print_args_echo(t_cmd *list, int flag_int, char *cmd, char *flag);
void	init_shell(t_shell **shell);
t_env	*make_list(t_shell **shell, char **envp);
void	free_env_mtx(char **env, int env_n, char **paths, int paths_n);
void	free_nodes(t_shell **shell);


#endif
