/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 23:43:39 by                   #+#    #+#             */
/*   Updated: 2022/01/25 14:33:20 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

t_list	*ft_find_remainder(t_list **lst, t_list **prev, int fd)
{
	t_list	*tmp;
	t_list	*list;
	t_list	*p;

	tmp = *lst;
	p = NULL;
	while (tmp)
	{
		if (tmp->fd == fd)
		{
			*prev = p;
			return (tmp);
		}
		p = tmp;
		tmp = tmp->next;
	}
	list = malloc(sizeof(t_list));
	if (list == NULL)
		return (NULL);
	list->fd = fd;
	list->remainder = NULL;
	tmp = *lst;
	list->next = tmp;
	*lst = list;
	return (list);
}

char	*ft_strdup(const char *src)
{
	int		l;
	int		i;
	char	*dest;

	l = 0;
	if (!src)
		return (NULL);
	while (src[l])
		l++;
	dest = malloc(l + 1);
	if (dest == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (i <= l)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	size_t		l;

	if (dest == NULL && src == NULL)
		return (NULL);
	d = (char *)dest;
	s = (const char *)src;
	l = 0;
	while (l < n)
	{
		d[l] = s[l];
		l++;
	}
	return (dest);
}

static size_t	ft_max_size(void)
{
	size_t	max_size;
	size_t	bits;

	max_size = 1;
	bits = sizeof(size_t) * 8;
	while (bits--)
	{
		max_size = max_size * 2;
	}
	return (max_size - 1);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	max_size;
	size_t	len;
	size_t	len1;
	size_t	len2;
	char	*s;

	if (s1 == NULL)
		return (ft_strdup(s2));
	max_size = ft_max_size();
	len1 = 0;
	while (s1[len1] != '\0')
		len1++;
	len2 = 0;
	while (s2[len2] != '\0')
		len2++;
	if ((len1 != max_size) && ((max_size - len1 - 1) >= len2))
		len = len1 + len2;
	else
		return (NULL);
	s = (char *)malloc(len + 1);
	if (s == NULL)
		return (NULL);
	ft_memcpy((void *)s, (const void *)s1, len1);
	ft_memcpy((void *)(s + len1), (const void *)s2, len2 + 1);
	return (s);
}
