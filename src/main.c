/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:19:45 by root              #+#    #+#             */
/*   Updated: 2023/07/24 11:48:48 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	g_signal;

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	if (argc != 1 || argv[1] != NULL)
	{
		printf("minishell: too many arguments\n");
		exit(1);
	}
	shell = (t_shell *)ft_calloc(1, sizeof(t_shell));
	init_shell(&shell);
	shell->env = make_list(&shell, envp);
	shell->std_io[0] = dup(0);
	shell->std_io[1] = dup(1);
	minishell(&shell);
	free (shell);
}
