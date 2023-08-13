#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

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
	char			**env_mtx;
	char			**paths_mtx;
	char			*heredoc_name;
	int				count;
	int				env_n;
	int				paths_n;
	int				pipelist_n;
	t_block			*pipelist;
	t_block			*previous;
	t_env			*env;
	t_env			*exit_code_var;
	t_env			*env_last;
	u_int8_t		exit_code;
}					t_shell;

#endif