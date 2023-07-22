/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:01:15 by root              #+#    #+#             */
/*   Updated: 2023/07/22 16:31:08 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	c_exit(t_shell **shell)
{
	// if ((*shell)->flag)
	// {
	// 	write(2, "haha", 4);
	// 	exit_code = 2;
	// }
	rl_clear_history();
	free_pipe_list(shell, (*shell)->pipelist);
	exit((*shell)->exit_code);
}
