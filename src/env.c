#include "../headers/minishell.h"

void	c_env(t_shell **shell)
{
	// int var_len;
	// int msg_len;

	shell = (shell);
    // if (!is_flag_null(shell, ""))
    //     return ;
    // while ((*shell)->env != NULL)
    // {
    //     if ((*shell)->env->type != LOCAL && (*shell)->env->msg)
	// 	{
	// 		var_len = ft_strlen((*shell)->env->var);
	// 		msg_len = ft_strlen((*shell)->env->msg);
    //         write(1, (*shell)->env->var, var_len);
	// 		write(1, "=", 1);
    //         write(1, (*shell)->env->msg, msg_len);
	// 		write(1, "\n", 1);
	// 	}
    //     (*shell)->env = (*shell)->env->next;
    // }
}

char	**make_path(t_shell **shell, char **envp)
{
	char	**path_in;
	while(ft_strncmp(*envp, "PATH", 4))
		envp++;
	*envp += 5;
	path_in = split_path(shell, *envp, ':');
	(*shell)->path_in_n = (*shell)->count;
	return (path_in);
}

char	**make_env(t_shell **shell, char **envp, int set)
{
	char	**env_in;
	char	**env_in_tmp;
	char	**envp_tmp;

	envp_tmp = envp;
	if (set)
	{
		env_in = (char **)ft_calloc((*shell)->env_in_n + 1, sizeof(char *));
		env_in_tmp = env_in;
	}
	while (*envp_tmp)
	{
		(*shell)->env_in_n += (set == 0);
		if (set)
			*env_in_tmp = *envp_tmp;
		envp_tmp += 1;
		env_in_tmp += (set == 1);
	}
	if (!set)
		return (make_env(shell, envp, 1));
	env_in_tmp = NULL;
	return (env_in);
}
