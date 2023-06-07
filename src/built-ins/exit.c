#include "../headers/minishell.h"

void	c_exit(t_shell **shell)
{
	int exit_code;

	exit_code = 0;
	if ((*shell)->flag)
	{
		// printf("minishell: %s: %s: invalid option\n", (*shell)->command,
		// (*shell)->flag);
		write(2, "haha", 4);
		exit_code = 2;
	}
	rl_clear_history();
	free_list((*shell)->env);
	free_pipe_list(shell, (*shell)->pipelist);
	exit(exit_code);
}