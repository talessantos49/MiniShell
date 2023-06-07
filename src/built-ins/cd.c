#include "../headers/minishell.h"

void	update_var(t_shell **shell, char *name, char *value)
{
	t_env	*env;

	env = find_arg(shell, name);
	if (env)
	{
		free(env->msg);
		env->msg = ft_strdup(value);
	}
}

void	c_cd(t_shell **shell)
{
	t_env	*var;
	char	*oldpwd;
	char	buf[256];

	shell = (shell);
	if (!is_flag_null(shell, ""))
		return ;
	if (!(*shell)->content && !(*shell)->flag)
		(*shell)->content = getenv("HOME");
	else if (!strcmp_mod((*shell)->flag, "-"))
	{
		var = find_arg(shell, "OLDPWD");
		(*shell)->content = var->msg;
		printf("%s\n", (*shell)->content);
	}
	var = find_arg(shell, "PWD");
	oldpwd = var->msg;
	if (chdir((*shell)->content) != 0)
		printf("bash: cd: %s: No such file or directory\n", \
		(*shell)->content);
	else
	{
		rl_redisplay();
		update_var(shell, "OLDPWD", oldpwd);
		update_var(shell, "PWD", getcwd(buf, 256));
	}
}
