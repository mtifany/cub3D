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

static char	*ft_new_line_processing(t_list *rlst, char *nl_at)
{
	char	*result;
	size_t	l;

	result = (char *)malloc(nl_at - rlst->remainder + 2);
	if (result)
	{
		l = 0;
		while (l < (size_t)(nl_at - rlst->remainder + 1) && rlst->remainder[l])
		{
			result[l] = rlst->remainder[l];
			l++;
		}
		result[l] = '\0';
	}
	nl_at = ft_strdup(nl_at + 1);
	free(rlst->remainder);
	if (result != NULL && nl_at != NULL)
	{
		rlst->remainder = nl_at;
		return (result);
	}
	free(nl_at);
	rlst->remainder = NULL;
	free(result);
	return (NULL);
}

static char	*ft_strchr(const char *s, size_t *i, int c)
{
	size_t	j;

	if (!s)
		return (NULL);
	j = *i;
	while (s[j] && s[j] != c)
	{
		j++;
	}
	if (s[j] == c)
	{
		return ((char *)(s + j));
	}
	*i = j;
	return (NULL);
}

char	*ft_endoffile_emptyline_processing(t_list *rlst)
{
	char	*result;

	if (!*(rlst->remainder))
	{
		free(rlst->remainder);
		result = NULL;
	}
	else
		result = rlst->remainder;
	rlst->remainder = NULL;
	return (result);
}

char	*ft_remainder(int fd, t_list *rlst, char *buffer, size_t i)
{
	char	*new_line_at;
	char	*result;
	int		cbytes;

	new_line_at = ft_strchr(rlst->remainder, &i, '\n');
	if (new_line_at)
		return (ft_new_line_processing(rlst, new_line_at));
	cbytes = read(fd, buffer, BUFFER_SIZE);
	if (cbytes == 0 && rlst->remainder)
		return (ft_endoffile_emptyline_processing(rlst));
	else if (cbytes > 0)
	{
		buffer[cbytes] = '\0';
		result = rlst->remainder;
		rlst->remainder = ft_strjoin(result, buffer);
		free(result);
		if (!rlst->remainder)
			return (NULL);
		return (ft_remainder(fd, rlst, buffer, i));
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	t_list			*rlst;
	char			*result;
	char			*buffer;
	t_list			*prev;

	prev = NULL;
	rlst = ft_find_remainder(&lst, &prev, fd);
	buffer = (char *) malloc(BUFFER_SIZE + 1);
	if (!rlst || !buffer || read(fd, buffer, 0) < 0)
		result = NULL;
	else
		result = ft_remainder(fd, rlst, buffer, 0);
	if (rlst && !result)
	{
		if (!prev)
			lst = rlst->next;
		else
			prev->next = rlst->next;
		free(rlst->remainder);
		free(rlst);
	}
	free(buffer);
	return (result);
}
