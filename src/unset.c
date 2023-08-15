/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:29:34 by root              #+#    #+#             */
/*   Updated: 2023/07/19 09:18:55 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	c_unset(t_shell **shell)
{
	t_cmd	*current;
	t_env	*var_prev;
	t_env	*var_target;

	current = (*shell)->pipelist->commands->next;
	if (!current || (current && current->arg[0] == CHAR_MINUS))
	{
		if (current->arg[0] == CHAR_MINUS)
			ft_printfd(ERROR_OPTION, STDERR_FILENO, NAME_UNSET);
		return ;
	}
	while (current && current->arg)
	{
		var_prev = find_var(shell, current->arg, ft_strlen(current->arg), 1);
		if (var_prev)
		{
			if (var_prev->next)
			{
				var_target = var_prev->next;
				var_prev->next = var_target->next;
			}
			else
			{
				var_target = var_prev;
				safe_free(&var_target->key);
				safe_free(&var_target->value);
			}
			safe_free(&var_target);
			(*shell)->env_n -= 1;
		}
		current = current->next;
	}
}
