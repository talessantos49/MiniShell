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
	t_env	*node;

	if ((*shell)->content)
	{
		node = find_arg(shell, (*shell)->content);
		if (is_flag_null(shell, "") && node != NULL \
		&& node->type != ENVP)
		{
			if ((*shell)->env == node)
				(*shell)->env = node->next;
			else
				node->prev->next = node->next;
			if (node->next != NULL)
				node->next->prev = node->prev;
			free(node->var);
			free(node->msg);
			free(node);
		}
	}
}