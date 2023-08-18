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

static int	print_oldpwd(char *new_path, int error)
{
	if (new_path)
		ft_printf("%s\n", new_path);
	else if (!new_path && ++error)
		ft_printfd(ERROR_CD2, STDERR_FILENO);
	return (error);
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
	else if ((*shell)->pipelist->args[1][0] == CHAR_MINUS)
	{
		new_path = (find_var(shell, "OLDPWD", 6, 0))->value;
		error = print_oldpwd(new_path, error);
	}	
	if (chdir(new_path) < 0 && ++error == 1)
		ft_printfd(ERROR_CD3, STDERR_FILENO, new_path);
	if (error)
	{
		(*shell)->exit_code = 1;
		return ;
	}
	export_var(shell, "OLDPWD", old_path);
	export_var(shell, "PWD", new_path);
}
