#include "../headers/minishell.h"

void	print_export(t_shell **shell)
{
	while ((*shell)->env != NULL)
	{
		/*
		// Colocar em ordem alfabética
		*/
		if ((*shell)->env->type != LOCAL)
		{
			printf("declare -x %s", (*shell)->env->var);
			if ((*shell)->env->msg)
				printf("=\"%s\"", (*shell)->env->msg);
			printf("\n");
		}
		(*shell)->env = (*shell)->env->next;
	}
}

void	c_export(t_shell **shell)
{
	shell = (shell);
	if (!strcmp_mod((*shell)->command, "export"))
	{
		if (!is_flag_null(shell, ""))
			return ;
		if (!(*shell)->content)
			print_export(shell);
		else
			apart_args(shell, ' ', add_export);
	}
}

void	add_export(t_shell **shell)
{
	t_env	*node;
	char	*var;
	char	*msg;

	if (!is_args(shell))
		return ;
	var = strchr_rev((*shell)->content, '=');
	if (!var)
		var = ft_strdup((*shell)->content);
	msg = strchr_mod((*shell)->content, '=');
	node = find_arg(shell, var);
	if (node)
	{
		node->type = GLOBAL;
		free(var);
		if (msg)
		{
			free(node->msg);
			node->msg = ft_strdup(msg);
		}
	}
	else
	{
		node = insert_front(node, var, msg, GLOBAL);
		insert_last(&(*shell)->env, node);
	}
}
