/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:01:15 by root              #+#    #+#             */
/*   Updated: 2023/07/15 20:01:52 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	c_exit(t_shell **shell)
{
	if ((*shell)->pipelist->args[1])
	{
		ft_printfd(ERROR_OPTION, STDERR_FILENO, NAME_EXIT);
		(*shell)->exit_code = 2;
		return ;
	}
	free_shell(shell);
	exit(EXIT_SUCCESS);
}
