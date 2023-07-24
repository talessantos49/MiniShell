/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:49:31 by root              #+#    #+#             */
/*   Updated: 2023/07/24 01:30:10 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	cd_home(t_shell **shell)
{
	char	directory[1024];
	t_cmd	*temp_cmd;

	temp_cmd = (*shell)->pipelist->commands->next;
	if (temp_cmd)
	{
		replace_word(temp_cmd->arg, "~", getenv("HOME"), 0);
		if (chdir(temp_cmd->arg) == 0)
			if (getcwd(directory, sizeof(directory)) != NULL)
				(*shell)->actual_path = directory;
	}
}

void	c_cd(t_shell **shell)
{
	char	directory[1024];
	t_cmd	*temp_cmd;

	temp_cmd = (*shell)->pipelist->commands->next;
	if (temp_cmd)
	{
		if (find(temp_cmd->arg, '~'))
		{
			cd_home(shell);
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
