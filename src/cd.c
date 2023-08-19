/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:49:31 by root              #+#    #+#             */
/*   Updated: 2023/08/15 19:50:19 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char *oldpwd_switch(t_shell **shell)
{
	t_env	*var;

	var = find_var(shell, "OLDPWD", 6, 0);
	if (var)
	{
		ft_printf("%s\n", var->value);	
		return (var->value);
	}
	else
	{
		ft_printfd(ERROR_CD2, STDERR_FILENO);
		return (NULL);
	}

}

int	error_break(t_shell **shell, int error)
{
	if (error)
	{
		(*shell)->exit_code = 1;
		return (TRUE);
	}
	return (FALSE);

}

void	c_cd(t_shell **shell)
{
	char	buf[BUF];
	char	*new_path;
	char	*old_path;
	int		error;

	error = 0;
	old_path = getcwd(buf, BUF);
	if ((*shell)->pipelist->args[1])
		new_path = (*shell)->pipelist->args[1];
	if ((*shell)->pipelist->commands_n > 2 && ++error)
		ft_printfd(ERROR_CD1, STDERR_FILENO);
	else if (!(*shell)->pipelist->args[1] || !*(*shell)->pipelist->args[1] \
	|| strchr_mod((*shell)->pipelist->args[1], CHAR_TILDE))
		new_path = (find_var(shell, "HOME", 4, 0))->value;
	if ((*shell)->pipelist->args[1] \
	&&	(*shell)->pipelist->args[1][0] == CHAR_MINUS)
	{
		new_path = oldpwd_switch(shell);
		error += (new_path == NULL);
	}
 	if (new_path && chdir(new_path) < 0 && ++error == 1)
		ft_printfd(ERROR_CD3, STDERR_FILENO, new_path);
	if (error_break(shell, error))
		return ;
	export_var(shell, "OLDPWD", old_path);
	export_var(shell, "PWD", new_path);
}
