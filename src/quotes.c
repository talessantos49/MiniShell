/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:46:35 by root              #+#    #+#             */
/*   Updated: 2023/07/15 20:49:50 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	quote_clean(t_block *current, char *command, char quote)
{
	char	*quote_ptr;

	current->cmd = ft_strtrim(command, &quote);
	quote_ptr = current->cmd;
	while (quote_ptr)
	{
		quote_ptr = ft_strchr(quote_ptr, quote);
		if (!quote_ptr || !*quote_ptr)
			break ;
		quote_ptr[0] = 1;
		quote_ptr += 1;
	}
}

char	*quote_append(char **current, char *append, int newline)
{
	char	*new;
	char	*new_appd;
	int		appd_len;
	int		crrt_len;

	if (!*current)
		*current = "";
	crrt_len = ft_strlen(*current);
	appd_len = ft_strlen(append);
	new = (char *)ft_calloc((crrt_len + appd_len) + newline, sizeof(char));
	new_appd = new + crrt_len + newline;
	ft_strlcpy(new, *current, (crrt_len + appd_len) + 1);
	ft_strlcpy(new_appd - 1, "\n", (newline * 2));
	ft_strlcpy(new_appd, append, appd_len + 1);
	safe_free((void **)current);
	return (new);
}

int	quote_nested(char *string, char quote)
{
	char	*quote_pair;

	while (*string)
	{
		quote_pair = ft_strchr(string, quote);
		if (!quote_pair)
			break ;
		quote_pair = ft_strchr(quote_pair + 1, quote);
		if (!quote_pair)
			return (1);
		else
			string = quote_pair + 1;
	}
	return (0);
}

char	*quote_unclosed(t_block *current, char *input)
{
	char	**final_str;
	char	*quote_break;

	quote_break = NULL;
	new_command(current);
	signal_listener(signal_set, handle_sigint);
	final_str = &current->commands->arg;
	*final_str = quote_append(&current->commands->arg, input, 0);
	while (1 && !quote_break)
	{
		input = readline("> ");
		*final_str = quote_append(&current->commands->arg, input, 1);
		if (quote_nested(input, current->current_command->quote))
			break ;
	}
	add_history(*final_str);
	return ("\0");
}

int	is_quote(t_block *current, char line)
{
	if (line == '\'')
		current->quote = '\'';
	else if (line == '\"')
		current->quote = '\"';
	else
		return (0);
	return (1);
}
