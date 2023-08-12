/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:52:02 by macarval          #+#    #+#             */
/*   Updated: 2023/07/19 16:38:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef   MINISHELL_H
# define  MINISHELL_H

# include				<fcntl.h>
# include 				<readline/history.h>
# include 				<readline/readline.h>
# include 				<stdarg.h>
# include 				<string.h>
# include 				<sys/types.h>
# include 				<sys/uio.h>
# include 				<sys/wait.h>
# include 				<signal.h>
# include 				<stdio.h>
# include 				<stdlib.h>
# include 				<unistd.h>
# include 				"../libs/libft/libft.h"

# define  BUF	 		256
# define  CHAR_EQUAL	'='
# define  CHAR_MINUS	'-'
# define  CHAR_Q_DOUBLE '\"'
# define  CHAR_Q_SINGLE	'\''
# define  CHAR_TILDE	'~'
# define  CHAR_VAR 		'$'
# define  CHMOD	 		0644
# define  COLOR_BHCYAN	"\001\e[1;96m\002"
# define  COLOR_BHRED	"\001\e[1;91m\002"
# define  COLOR_RESET  	"\001\e[0m\002"
# define  ERROR_ARG		"MiniShell: too many arguments\n"
# define  ERROR_CD1		"MiniShell: cd: too many arguments\n"
# define  ERROR_CD2		"MiniShell: cd: OLDPWD not set\n"
# define  ERROR_CD3		"MiniShell: cd: %s: No such file or directory\n"
# define  ERROR_CMD		"%s: command not found\n"
# define  ERROR_EXPORT	"MiniShell: export: `%s': not a valid identifier\n"
# define  ERROR_FD_DIR	"MiniShell: %s: No such file or directory\n"
# define  ERROR_IO_CHAR "MiniShell: syntax error near unexpected token `%s%c'\n"
# define  ERROR_IS_DIR	"MiniShell: %s: Is a directory\n"
# define  ERROR_OPTION 	"%s: invalid option or argument\n"
# define  KEY_HOME		"HOME"
# define  KEY_PWD		"PWD"
# define  KEY_OLDPWD	"OLDPWD"
# define  NAME_CD		"cd"
# define  NAME_ECHO		"echo"
# define  NAME_EXIT		"exit"
# define  NAME_ENV		"env"
# define  NAME_EXIT		"exit"
# define  NAME_EXPORT	"export"
# define  NAME_PWD		"pwd"
# define  NAME_UNSET	"unset"
# define  STR_FLAG_ECHO "-n"
# define  STR_HEREDOC	".tmp"
# define  STR_NEWLINE 	"newline"
# define  STR_QUOTES 	"\'\""
# define  STR_SLASH 	"/"
# define  STR_SPACES 	" \t\r\f\v"
# define  STR_SPECIALS 	"<>|"
# define  STR_VOID 		""

extern int			g_signal;

enum	e_bool
{
	FALSE,
	TRUE
};

enum	e_quote
{
	QUOTE_OPEN = 1,
	QUOTE_CLOSE
};

enum	e_return
{
	SUCCES,
	EXCEPTION
};

enum	e_set
{
	NEW_BLOCK, 
	COMMAND, 
	INFILE, 
	OUTFILE_NEW, 
	OUTFILE_APPEND, 
	TEST_HEREDOC
};

typedef struct s_env
{
	char			*key;
	char			*value;
	int				is_exported;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			*arg;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_quote
{
	char			quote;
	struct s_quote	*next;
}					t_quote;

typedef struct s_block
{
	char			**args;
	char			*expand;
	char			*arg_0;
	char			*cmd;
	char			*heredoc_name;			
	enum e_set		set;
	int				commands_n;			
	int				fd[2];
	int				pipe[2];
	int				signal;
	int				quotes_n;			
	pid_t			pid;
	struct s_block	*next;
	t_cmd			*commands;
	t_cmd			*current_command;
	t_quote			*current_quote;
	t_quote			*quotes_list;
	void			(*built_in)(void *shell);
}					t_block;

typedef struct s_shell
{
	char		**env_mtx;
	char		**paths_mtx;
	char		*heredoc_name;
	int			count;
	int			env_n;
	int			paths_n;
	int			pipelist_n;
	t_block		*pipelist;
	t_block		*previous;
	t_env		*env;
	t_env		*exit_code_var;
	t_env		*env_last;
	u_int8_t	exit_code;
}				t_shell;

// base
void	minishell(t_shell **shell);
void	execution(t_shell **shell, t_block *current);
void	free_pipe_list(t_shell **shell, t_block *current);
void	safe_free(void *pointer);
void	free_execve_env_matrix(t_shell **shell);
void    free_shell(t_shell **shell);

// Split

// Built-in's
void	*is_built_in(char *command);
void	c_cd(t_shell **shell);
void	c_echo(t_shell **shell);
void	c_env(t_shell **shell);
void	c_exit(t_shell **shell);
void	c_export(t_shell **shell);
void	c_pwd(t_shell **shell);
void	c_unset(t_shell **shell);

//	Heredoc

void	heredoc_name_setup(t_shell **shell, t_block *current);
void	here_doc_exec(t_shell **shell, t_block *current, char *delimiter);
char	*here_doc_setup(t_shell **shell, t_block *current, char *line);

// Env
void	make_env(t_shell **shell, char **envp);
void	print_env(t_shell **shell, int is_export);
void	export_var(t_shell **shell, char *key, char *value);
void	export_new_var(t_shell **shell, char *key, char *value);
t_env	*find_var(t_shell **shell, char *key, int key_len, int is_unset);

// Utils
int		strcmp_mod(const char *s1, const char *s2);
char	*strchr_mod(const char *str, int c);
char	**split_commands(t_shell **shell, char *s, char c);

//	Signals
void	handle_sigquit(t_shell **shell);
void	handle_sigint(int signal);
void	signal_listener(__sighandler_t handle_quit, __sighandler_t handle_int);
void	signal_handled_exec(t_shell **shell);


//	PipeList Build
t_block	*new_block_on_pipe_list(t_shell **shell, t_block *block_current);
void 	pipe_list_build(t_shell **shell, char *line);
void	new_command(t_block *current);
char	*is_no_word(t_shell **shell, t_block *current, char *line);
char	*is_spaces(char *line, char *spaces);
char	*is_quote(t_block *current, char *line);
char	*is_command(t_shell **shell, t_block *current, char *line);
char	*is_file_io(t_shell **shell, t_block *current, char *line);
char	*is_special(t_shell **shell, \
t_block *current, char *line, char *specials);
char 	*special_cases(t_shell **shell, t_block *current, char *line);
void	is_var(t_shell **shell, t_block *current, char *arg, int arg_len);


// 	Quotes
char	*quotes_clean(t_block *current, char **arg, int arg_len);
void 	manage_file_descriptors(t_block *current, char *file_name);
void	execve_matrixes(t_shell **shell, t_block *current);
void	execve_env_matrix(t_shell **shell, t_env *current, int env_n);

#endif