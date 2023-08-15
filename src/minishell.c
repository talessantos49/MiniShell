/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:02:28 by macarval          #+#    #+#             */
/*   Updated: 2023/07/19 07:56:27 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	minishell(t_shell **shell)
{
	char	*line;

	signal_listener(SIG_IGN, handle_sigint);
	while (TRUE)
	{
		line = readline(COLOR_BHCYAN "MiniShell" COLOR_BHRED "$" \
		COLOR_BHCYAN "> " COLOR_RESET);
		(*shell)->exit_code = 0;
		if (line && *line)
		{
			add_history(line);
			pipe_list_build(shell, line);
			execution(shell, (*shell)->pipelist);
			free_pipe_list(shell, (*shell)->pipelist);
			safe_free(&line);
		}
		else if (line == NULL)
		{
			safe_free(&line);
			handle_sigquit(shell);
		}
	}
}
