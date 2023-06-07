#include "../headers/minishell.h"

void	c_pwd(t_shell **shell)
{
	char	buf[256];

	shell = (shell);
	if (!is_flag_null(shell, ""))
		exit(2);
	printf("%s\n", getcwd(buf, 256));
}
