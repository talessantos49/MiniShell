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
	shell = (t_shell *)ft_calloc(1, sizeof(t_shell));
	shell->env_in = make_env(&shell, envp, 0);
	shell->path_in = make_path(&shell, envp);
	shell->std_io[0] = dup(0);
	shell->std_io[1] = dup(1);
	minishell(&shell);
}
