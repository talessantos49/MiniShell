#include "../headers/minishell.h"

void	*ff_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	int		result;
	void	*s;

	result = nmemb * size;
	if (result == 0 || result / size != nmemb)
		return (NULL);
	ptr = (void *)malloc(result);
	s = ptr;
	while (result--)
		*(unsigned char *)s++ = 0;
	return (ptr);
}

static char	*ff_strchr(char *s, int c)
{
	char	*ptr;

	ptr = s;
	while (ptr && *ptr && *ptr != (unsigned char)c)
		ptr++;
	if (*ptr == (unsigned char)c)
		return (ptr);
	return (NULL);
}

static char	*ff_substr(char *s, unsigned int start, size_t len)
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
	ptr = ff_calloc(len + 1, sizeof(char));
	while (len-- && s[start])
		ptr[index++] = s[start++];
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
		p_chr = ff_strchr(p, *c);
		(*shell)->count += (*p && *p != *c);
		if (p && *p && mtx != NULL)
			mtx[(*shell)->count - 1] = ff_substr(p, 0, p_chr - p);
	}
	if (mtx == NULL)
	{
		mtx = (char **)ff_calloc((*shell)->count + 1, sizeof(char *));
		return (ft_mtx(shell, s, c, mtx));
	}
	mtx[(*shell)->count] = 0;
	return (mtx);
}

char	**split_commands(t_shell **shell, char *s, char c)
{
	return (ft_mtx(shell, s, &c, NULL));
}
