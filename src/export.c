/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:02:11 by root              #+#    #+#             */
/*   Updated: 2023/08/16 19:29:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	export_new_var(t_shell **shell, char *key, char *value)
{
	t_env	*new_var;
	int		value_len;

	new_var = (t_env *)ft_calloc(1, sizeof(t_env));
	(*shell)->env_last->next = new_var;
	(*shell)->env_last = new_var;
	new_var->key = key;
	if (value)
	{
		value_len = ft_strlen(value);
		if (value_len == 1 && value[0] == '=')
			value[0] = 1;
		else
			value += 1;
		new_var->value = ft_substr(value, 0, ft_strlen(value));
	}
	(*shell)->env_n += 1;
}

void	export_var(t_shell **shell, char *key, char *value)
{
	t_env	*var;
	int		value_len;

	var = find_var(shell, key, ft_strlen(key), 0);
	if (!var)
		export_new_var(shell, key, value);
	else if (var)
	{
		if (value)
		{
			value_len = ft_strlen(value);
			if (value_len == 1 && value[0] == '=')
				value[0] = 1;
			else if (value[0] == '=')
				value += 1;
			var->value = ft_substr(value, 0, value_len + 1);
		}
	}
}

static int	is_valid_key(char *arg)
{
	if (!ft_isdigit(*arg))
	{
		while (*arg && (ft_isalnum(*arg) || (*arg == '_')))
			arg++;
		if (!*arg)
			return (TRUE);
	}	
	return (FALSE);
}

void	c_export(t_shell **shell)
{
	t_cmd	*current;
	char	*key;
	char	*value;

	current = (*shell)->pipelist->commands->next;
	if (!current)
		return (print_env(shell, 1));
	while (current && current->arg)
	{
		value = ft_strchr(current->arg, '=');
		if (value && value != current->arg)
		{
			key = (char *)ft_calloc((value - current->arg + 1), sizeof(char));
			ft_strlcpy(key, current->arg, (value - current->arg + 1));
		}
		else
			key = ft_substr(current->arg, 0, ft_strlen(current->arg));
		if (is_valid_key(key))
			export_var(shell, key, value);
		else
		{
			(*shell)->exit_code = 1;
			ft_printfd(ERROR_EXPORT, STDERR_FILENO, key);
		}
		current = current->next;
	}
}
