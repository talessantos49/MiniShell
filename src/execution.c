#include "../headers/minishell.h"

static char	*ff_strjoin(char *s1, char *s2)
{
	char	*ptr;
	char	*ptr_2;
	int		ln1;
	int		ln2;

	ptr = s1;
	ptr_2 = s2;
	ln1 = 1;
	ln2 = 1;
	while (*++ptr)
		ln1++;
	while (*++ptr_2)
		ln2++;
	ptr = ff_calloc((ln1 + ln2) + 2, sizeof(char));
	ptr_2 = (ptr + ln1);
	ptr_2++;
	if (ptr != NULL)
	{
		while (--ln1 > -1)
			ptr[ln1] = s1[ln1];
		*(ptr_2 - 1) = '/';
		while (--ln2 > -1)
			ptr_2[ln2] = s2[ln2];
	}
	return (ptr);
}

void close_all_pipes(t_block *current)
{
	while (current && current->pipe[0])
	{
		close(current->pipe[0]);
		close(current->pipe[1]);
		current = current->next;
	}
}

void pipeline_manager(t_shell **shell, t_block *current)
{
	if (current->fd[0])
	{
		dup2(current->fd[0], STDIN_FILENO);
		close(current->fd[0]);
	}
	if (current->pipe[0] && current->pipe[1])
	{
		dup2(current->pipe[1], STDOUT_FILENO);
		close_all_pipes((*shell)->pipelist);
	}
	if (current->fd[1])
	{
		dup2(current->fd[1], STDOUT_FILENO);
		close(current->fd[1]);
	}
}

static void	signal_handle(t_shell **shell)
{
	signal_listener(NULL, signal_set);
	if (shell)
		shell = NULL;
	// if (g_signal == SIGINT)
	// 	handle_sigint(shell);
}

void child(t_shell **shell, t_block *current)
{
	signal_handle(shell);
	pipeline_manager(shell, current);
	if (current->built_in)
	{
		current->built_in(shell); 
		if (!((*shell)->pipelist == current && current->pipe[0] == 0))
			exit(0);
		else
			restore_std_io((*shell)->std_io);
	}
	else if (execve(current->cmd, current->args, (*shell)->env_mtx) < 0)
	{
		perror(current->cmd);
		exit(-1);
	}
}

int command_validate(t_shell **shell, t_block *current)
{
	char	*cmd_tmp;
	int		i;

	i = -1;
	if (current->built_in)
		return (builtin_setup(shell, current->args));
	while (++i < (*shell)->paths_n)
	{
		cmd_tmp = ff_strjoin((*shell)->paths_mtx[i], current->cmd);
		if (!(access(cmd_tmp, X_OK)))
		{
			safe_free((void **)&current->cmd);
			current->cmd = cmd_tmp;
			return (0);
		}
		else
			safe_free((void **)&cmd_tmp);
	}
	if (!(access(current->args[0], X_OK)))
	{
		current->cmd = ft_strdup(current->args[0]);
		return (0);
	}
	(*shell)->exit_code = 127;
	perror_free(": command not found", current->cmd);
	return(1);
}

void execution(t_shell **shell, t_block *current)
{
	while (current && current->commands)
	{
		if(command_validate(shell, current))
		{
			current = current->next;
			continue;
		}
		signal_listener(NULL, SIG_IGN);
		if (!((*shell)->pipelist == current && current->pipe[0] == 0) 
		|| !current->built_in)
			(*shell)->pid = fork();
		if (!(*shell)->pid)
			child(shell, current);
		if (current->built_in || (*shell)->pipelist == current)
		{
			waitpid((*shell)->pid, NULL, 0);
			if (WIFEXITED((*shell)->status))
				(*shell)->exit_code = WEXITSTATUS((*shell)->status);
		}
		current = current->next;
	}
}

