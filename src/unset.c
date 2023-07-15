/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:29:34 by root              #+#    #+#             */
/*   Updated: 2023/07/15 20:29:35 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if ((*shell)->content)
	{
		return ;
	}
}
