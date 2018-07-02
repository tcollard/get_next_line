/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 15:45:20 by tcollard          #+#    #+#             */
/*   Updated: 2018/01/16 19:03:12 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_gnl	*new_fd(int fd)
{
	t_gnl	*new;

	if (fd < 0 || fd > 256)
		return (NULL);
	if (!(new = (t_gnl *)malloc(sizeof(t_gnl))))
		return (NULL);
	new->fd = fd;
	if (!(new->data = ft_memalloc((size_t)(BUFF_SIZE + 1))))
		return (NULL);
	new->next = NULL;
	new->ret_read = BUFF_SIZE;
	return (new);
}

static t_gnl	*get_fd(int fd, t_gnl **lst)
{
	t_gnl	*tmp;

	tmp = *lst;
	if (!(tmp))
	{
		tmp = new_fd(fd);
		*lst = tmp;
	}
	else
	{
		while (tmp->fd != fd && tmp->next)
			tmp = tmp->next;
		if (tmp->fd != fd)
		{
			tmp->next = new_fd(fd);
			tmp = tmp->next;
		}
	}
	return (tmp);
}

int				fill_line(t_gnl *lst, char **line, char *tmp)
{
	size_t	i;

	i = 0;
	if (lst->ret_read < BUFF_SIZE && lst->data[i] == '\0')
	{
		lst->fd = 300;
		return (0);
	}
	while (lst->data[i] != '\n' && lst->data[i] != '\0')
		i += 1;
	if (!(*line = (char *)ft_memalloc((size_t)(i + 1))))
		return (-1);
	*line = ft_strncpy(*line, lst->data, (size_t)i);
	if (lst->data[i] == '\0' && lst->ret_read == BUFF_SIZE)
	{
		free(*line);
		return (read_fd(lst, line));
	}
	tmp = ft_strsub(lst->data, (i + 1), (ft_strlen(lst->data) - i));
	free(lst->data);
	if (!(lst->data = ft_memalloc(ft_strlen(tmp) + 1)))
		return (-1);
	lst->data = ft_strcpy(lst->data, tmp);
	free(tmp);
	return (1);
}

int				read_fd(t_gnl *lst, char **line)
{
	char	*str;
	char	*tmp;

	tmp = NULL;
	if (!(str = ft_memalloc((size_t)(BUFF_SIZE + 1))))
		return (-1);
	if (lst->ret_read != BUFF_SIZE)
	{
		free(str);
		return (fill_line(lst, line, tmp));
	}
	if ((lst->ret_read = read(lst->fd, str, BUFF_SIZE)) == -1)
	{
		lst->fd = 300;
		free(str);
		return (-1);
	}
	if (!(tmp = ft_memalloc(ft_strlen(lst->data) + 1)))
		return (-1);
	tmp = ft_strcpy(tmp, lst->data);
	free(lst->data);
	lst->data = ft_strjoin(tmp, str);
	free(str);
	free(tmp);
	return (fill_line(lst, line, tmp));
}

int				get_next_line(const int fd, char **line)
{
	t_gnl			*tmp;
	static t_gnl	*lst;
	int				gnl;

	if (!(line))
		return (-1);
	if (!(tmp = get_fd(fd, &lst)))
		return (-1);
	gnl = read_fd(tmp, line);
	return (gnl);
}
