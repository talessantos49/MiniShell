/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:31:09 by root              #+#    #+#             */
/*   Updated: 2023/07/05 13:17:06 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../headers/minishell.h"

// char *is_enviroment(t_shell **shell, char *line)
// {
// 	char	*line_temp;
// 	char	*str_temp;
// 	// t_env	*new_arg;
// 	int	i;
// 	int	k;

// 	line_temp = line;
// 	i = 0;
// 	k = 0;
// 	// new_arg = (t_env *)ff_calloc(1, sizeof(t_env));
// 	if ((find(line_temp, '=')) == 1)
// 	{
// 		while(line_temp[i] != '=')
// 			i++;
// 		k = i;
// 		while((line_temp[k] != ' ' && line_temp[k] != '\0') || k == 0)
// 			k--;
// 		str_temp = ft_substr(line_temp, k + 1, i - k);
// 		str_temp = ft_substr(str_temp, 0, ft_strlen(str_temp) - 1);
// 		printf("%s\n", (*shell)->line);
// 		// new_arg->var = str_temp;
// 		// new_arg->msg = ft_substr(line_temp, i + 1, ft_strlen(line_temp) - i);
// 		// new_arg->type = 1;
// 		// add_node(&(*shell)->env, new_arg);
// 	}
// 	return (line);
// }