/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations_input3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 20:11:06 by root              #+#    #+#             */
/*   Updated: 2023/08/15 20:11:21 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	is_var(t_shell **shell, t_block *current, char *arg, int arg_len)
{
	if (current->set == TEST_HEREDOC || (current->current_quote \
	&& current->current_quote->quote == CHAR_Q_SINGLE))
		return ;
	if (*arg == CHAR_VAR || (current->expand \
	&& (arg != is_spaces(arg, STR_SPACES) || !*arg || *arg == CHAR_EQUAL \
	|| (current->current_quote && *arg == current->current_quote->quote))))
	{
		if (current->arg_0[1] == CHAR_QUESTION && (arg - current->arg_0) == 2)
		{
			current->arg_0 = ft_itoa((*shell)->exit_code);
			arg_len = ft_strlen(current->arg_0);
		}
		else
			arg_len = var_define(shell, current, (arg - current->arg_0));
		current->arg_0 = ft_substr(current->arg_0, 0, arg_len);
		current->expand = ft_strjoin(current->expand, current->arg_0);
		safe_free(&current->arg_0);
		current->arg_0 = arg;
	}
}