/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:29:34 by root              #+#    #+#             */
/*   Updated: 2023/07/16 10:16:06 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// void	c_unset(t_shell **shell)
// {
// 	shell = (shell);
// 	if (!strcmp_mod((*shell)->command, "unset"))
// 	{
// 		apart_args(shell, ' ', exe_unset);
// 	}
// }

void	exe_unset(t_shell **shell)
{
	if ((*shell)->content)
	{
		return ;
	}
}

void	c_unset(t_shell **shell)
{
	// t_env	*temp;

	// temp = find_arg(shell, (*shell)->pipelist->commands->next->arg);
	// printf("command: %s\n", (*shell)->pipelist->commands->arg);
	// printf("command: %s\n", (*shell)->command);
	if (is_var(shell, (*shell)->pipelist->commands->next->arg))
		printf("achei\n");
	else
	{
		(*shell)->exit_code = 0;
		printf("nao achei!\n");
	}
}

