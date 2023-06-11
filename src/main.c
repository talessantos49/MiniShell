#include "../headers/minishell.h"

int g_signal;

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	if (argc != 1 || argv[1] != NULL)
	{
		printf("minishell: too many arguments\n");
		exit(1);
	}
		// error(ERR_ARG, NULL, NO_FREE, EXIT_FAILURE);
	shell = (t_shell *)ff_calloc(1, sizeof(t_shell));
	shell->env = make_list(&shell, envp);
	shell->std_io[0] = dup(0);
	shell->std_io[1] = dup(1);
    minishell(&shell);
}
