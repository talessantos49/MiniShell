/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:49:31 by root              #+#    #+#             */
/*   Updated: 2023/07/23 12:30:49 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	c_cd(t_shell **shell)
{
	char	directory[1024];
	t_cmd	*temp_cmd;

	temp_cmd = (*shell)->pipelist->commands->next;
	if (temp_cmd)
	{
		if (find(temp_cmd->arg, '~'))
		{
			replace_word(temp_cmd->arg, "~", getenv("HOME"));
			if (chdir(temp_cmd->arg) == 0)
				if (getcwd(directory, sizeof(directory)) != NULL)
					(*shell)->actual_path = directory;
		}
		else if (chdir(temp_cmd->arg) == 0)
		{
			if (getcwd(directory, sizeof(directory)) != NULL)
				(*shell)->actual_path = directory;
		}
		else
		{
			printf("bash: cd: %s: No such file or directory\n", temp_cmd->arg);
			(*shell)->exit_code = 1;
			return ;
		}
	}
	(*shell)->exit_code = 0;
}
