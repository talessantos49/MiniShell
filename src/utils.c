#include "../headers/minishell.h"

char	*strchr_mod(const char *str, int c)
{
	if (str != NULL)
	{
		while (*str != '\0')
		{
			if (*str == (char) c)
			{
				str++;
				return ((char *)str);
			}
			str++;
		}
		if ((char) c == '\0' && *str == '\0')
			return ((char *)str);
	}
	return (NULL);
}

int	strcmp_mod(const char *s1, const char *s2)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s1);
	if (len != ft_strlen(s2))
		return (1);
	while (i < len)
	{
		if (s1[i] != s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
		{
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		}
		i++;
	}
	return (SUCCES);
}

char	*ft_strtrim(char const *s1, const char *set)
{
	char	*rev;
	char 	*s1_backup;
	char	*set_reset;
	char	*trim;

	s1_backup = (char *)s1;
	set_reset = (char *)set;
	rev = (char *)s1 + ft_strlen(s1) - 1;
	while (*set && *s1)
	{
		if (*s1 == *set || *rev == *set)
		{
			s1 += *s1 == *set;
			rev -= *rev == *set;
			set = set_reset;
		}
		else
			set++;
	}
	if (s1 == s1_backup && rev == s1_backup + ft_strlen(s1) - 1)
		return ((char *)s1);
	trim = ft_calloc(((rev - s1) + 2) * (*s1 > 0) + (*s1 == 0), sizeof(char));
	ft_strlcpy(trim, s1, ((rev - s1) + 2) * (*s1 > 0) + (*s1 == 0));
	return (trim);
}
