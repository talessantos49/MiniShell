#include "../headers/minishell.h"

void	free_split(char ***split)
{
	int		i;
	char	**temp;

	i = -1;
	temp = *split;
	while (temp[++i])
		free(temp[i]);
	free(*split);
}

t_env	*find_arg(t_shell **shell, char *var)
{
	t_env	*temp;

	temp = (*shell)->env;
	while (temp != NULL)
	{
		if (!strcmp_mod(temp->var, var))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	is_args(t_shell **shell)
{
	if ((*shell)->content[0] == '=' || ft_isdigit((*shell)->content[0]))
	{
		printf("bash: %s: `%s': not a valid identifier\n", \
		(*shell)->command, (*shell)->content);
		return (0);
	}
	return (1);
}

void	apart_args(t_shell **shell, char c, void (*function)(t_shell **shell))
{
	int		i;
	char	**split;

	i = -1;
	split = ft_split((*shell)->content, c);
	while (split[++i])
	{
		(*shell)->content = split[i];
		function(shell);
	}
	free_split(&split);
}
/////////////////////////////////////////////////////////ATENÇÃO



