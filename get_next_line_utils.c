/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 14:13:25 by dgutak            #+#    #+#             */
/*   Updated: 2023/07/17 14:40:31 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;

	res = malloc(nmemb * size);
	if (!res)
		return (0);
	ft_bzero(res, nmemb * size);
	return (res);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*temp;

	temp = (unsigned char *)s;
	while (n--)
	{
		*temp++ = '\0';
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ret;
	int		len;
	int		i;
	char	*temp;

	i = 0;
	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	temp = s1;
	if (!s2 || !s1)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	ret = ft_calloc((len + 1), sizeof(char));
	if (!ret)
		return (free(s1), NULL);
	while (len--)
	{
		if (*temp)
			ret[i++] = *temp++;
		else
			ret[i++] = *s2++;
	}
	return (free(s1), ret);
}

int	ft_strlen(const char *str)
{
	int	n;

	n = 0;
	if (!str)
		return (n);
	while (str[n] != '\0')
	{
		n++;
	}
	return (n);
}
