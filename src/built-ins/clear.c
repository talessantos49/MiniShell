#include "../headers/minishell.h"

void	c_clear(t_shell **shell)
{
	shell = (shell);
	if (!is_flag_null(shell, ""))
		return ;
	printf("\033[2J\033[1;1H");
}
