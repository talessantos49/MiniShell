#include "../headers/minishell.h"

void	c_unset(t_shell **shell)
{
	shell = (shell);
	if (!strcmp_mod((*shell)->command, "unset"))
	{
		apart_args(shell, ' ', exe_unset);
	}
}

void	exe_unset(t_shell **shell)
{
	if ((*shell)->content)
	{
		return ;
	}
}