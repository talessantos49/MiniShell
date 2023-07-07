#include "../headers/minishell.h"

static char	*mtx_substr(char *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	s_len;
	size_t	index;

	index = 0;
	s_len = 1;
	ptr = s;
	while (*++ptr)
		s_len++;
	if (start >= s_len)
		len = 0;
	else if (len > s_len - start)
		len = s_len - start;
	ptr = ft_calloc(len + 1, sizeof(char));
	while (len-- && s[start])
		ptr[index++] = s[start++];
	ptr[index] = '\0';
	return (ptr);
}

static char	**ft_mtx(t_shell **shell, char *s, char *c, char **mtx)
{
	char	*p;
	char	*p_chr;

	p = s;
	p_chr = p;
	(*shell)->count = 0;
	while (p_chr && p && *p && *p_chr)
	{	
		if (p_chr && *p_chr)
			p = p_chr;
		while (p_chr && *p && *p == *c && *c)
			p++;
		p_chr = ft_strchr(p, *c);
		(*shell)->count += (*p && *p != *c);
		if (p && *p && mtx != NULL)
			mtx[(*shell)->count - 1] = mtx_substr(p, 0, p_chr - p);
	}
	if (mtx == NULL)
	{
		mtx = (char **)ft_calloc((*shell)->count + 1, sizeof(char *));
		return (ft_mtx(shell, s, c, mtx));
	}
	mtx[(*shell)->count] = NULL;
	return (mtx);
}

char	**split_path(t_shell **shell, char *s, char c)
{
	return (ft_mtx(shell, s, &c, NULL));
}
