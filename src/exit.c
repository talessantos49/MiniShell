/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:01:15 by root              #+#    #+#             */
/*   Updated: 2023/08/18 12:18:59 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../inc/minishell.h"

// int	is_number(char *str)
// {
// 	str += (str[0] == CHAR_MINUS || str[0] == CHAR_PLUS);
// 	if (*str)
// 	{
// 		while (*str && ft_isdigit(*str))
// 			str++;
// 		if (!*str)
// 			return (TRUE);
// 	}
// 	return (FALSE);
// }


// void	c_exit(t_shell **shell)
// {
// 	int8_t	exit_code;

// 	if ((*shell)->pipelist->args[1] 
// 	&& !is_number((*shell)->pipelist->args[1]))
// 	{
// 		perror((*shell)->pipelist->args[1]);
// 		(*shell)->exit_code = 2;
// 	}
// 	else if ((*shell)->pipelist->args[1])
// 		(*shell)->exit_code = ft_atoi((*shell)->pipelist->args[1]);
// 	exit_code = (*shell)->exit_code;
// 	free_shell(shell);
// 	exit(exit_code);
// }


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:01:15 by root              #+#    #+#             */
/*   Updated: 2023/08/18 01:21:27 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	verify_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i]) || str[i] == '-' || str[i] == '+'))
			return (0);
		i += 1;
	}
	return (1);
}

int	transformation_atoi(char *str)
{
	int	i;
	int	exit_code;

	i = 0;
	exit_code = 0;
	i = ft_atoi(str);
	if (i <= 2147483647)
		exit_code = i;
	else
	{
		ft_printfd(ERROR_OPTION, STDERR_FILENO, NAME_EXIT);
		exit_code = 2;
	}
	return (exit_code);
}

void	c_exit(t_shell **shell)
{
	int	exit_code;

	exit_code = 0;
	if ((*shell)->pipelist->args[1] && !(*shell)->pipelist->args[2])
	{
		if (!verify_num((*shell)->pipelist->args[1]))
		{
			ft_printfd(ERROR_EXIT1, STDERR_FILENO, NAME_EXIT);
			exit_code = 2;
		}
		else
			exit_code = transformation_atoi((*shell)->pipelist->args[1]);
	}
	else if ((*shell)->pipelist->args[2])
	{
		ft_printfd(ERROR_EXIT, STDERR_FILENO, NAME_EXIT);
		exit_code = 1;
	}
	else
		(*shell)->exit_code = 0;
	free_shell(shell);
	exit(exit_code);
	return ;
}

// void	c_exit(t_shell **shell)
// {
// 	if ((*shell)->pipelist->args[1])
// 	{
// 		ft_printfd(ERROR_OPTION, STDERR_FILENO, NAME_EXIT);
// 		(*shell)->exit_code = 2;
// 		return ;
// 	}
// 	free_shell(shell);
// 	exit(EXIT_SUCCESS);
// }