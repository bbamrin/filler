/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 20:29:27 by pkathy            #+#    #+#             */
/*   Updated: 2019/09/29 16:35:03 by pkathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"
#include "get_next_line.h"

/*static t_fd_list	*search_fd(t_fd_list **lst, const int fd)
{
	t_fd_list			*local;

	local = *lst;
	while (local)
	{
		if (local->fd_num == fd)
			return (local);
		local = local->next;
	}
	if (!(local = (t_fd_list*)malloc(sizeof(t_fd_list))))
		return (NULL);
	local->content = (char*)malloc(1);
	((char*)local->content)[0] = '\0';
	local->fd_num = fd;
	local->next = NULL;
	ft_lstadd((t_list**)lst, (t_list*)local);
	return (local);
}

static int			copy_in_link(t_fd_list **lst, char **line)
{
	t_fd_list		*local;
	size_t			i;
	char			*str;
	size_t			len;
	char			*buf;

	i = 0;
	local = *lst;
	str = local->content;
	len = ft_strlen(str);
	while ((*str != '\n') && (*str != '\0'))
	{
		i++;
		str++;
	}
	if (!(*line = ft_strnew(i)))
		return (-1);
	ft_memcpy(*line, local->content, i);
	if (!(buf = ft_strnew(len - i)))
		return (-1);
	ft_memcpy(buf, ft_strchr((*lst)->content, '\n') + 1, len - i);
	free((*lst)->content);
	(*lst)->content = buf;
	return (1);
}

static int			free_fun(t_fd_list **local, int num)
{
	t_fd_list			*curr_list;
	t_fd_list			*prev_list;

	curr_list = *local;
	prev_list = *local;
	if (curr_list->fd_num == num)
		*local = curr_list->next;
	else
		while (curr_list)
		{
			prev_list = curr_list;
			curr_list = curr_list->next;
			if (curr_list->fd_num == num)
				break ;
		}
	prev_list->next = curr_list->next;
	if (curr_list->content)
		free(curr_list->content);
	free(curr_list);
	curr_list = NULL;
	return (0);
}

int					get_next_line(const int fd, char **line)
{
	static t_fd_list	*list_read_end = NULL;
	t_fd_list			*local;
	int					check;
	char				temp[BUFF_SIZE + 1];
	char				*tmp;

	if (fd < 0 || !line || BUFF_SIZE <= 0 || read(fd, NULL, 0) < 0
		|| !(local = search_fd(&list_read_end, fd)))
		return (-1);
	local->content = (!local->content) ? (ft_strnew(0)) : (local->content);
	if (ft_strchr(local->content, '\n'))
		return (copy_in_link(&local, line));
	while ((check = read(fd, temp, BUFF_SIZE)) > 0)
	{
		temp[check] = '\0';
		if (!(tmp = ft_strjoin(local->content, temp)))
			return (-1);
		free(local->content);
		local->content = tmp;
		if (ft_strchr(local->content, '\n'))
			break ;
	}
	if (check == 0 && (!(local->content) || ((char*)local->content)[0] == '\0'))
		return (free_fun(&list_read_end, local->fd_num));
	return (copy_in_link(&local, line));
}*/

size_t	len(char *str)
{
	return (ft_strlen(str));
}

int		k(char *n)
{
	return ((n) ? (1) : (0));
}

int		read_file(int fd, char **a, char **n)
{
	int		r;
	char	*temp;
	char	*buf;

	r = 0;
	if (!(buf = ft_strnew(BUFF_SIZE)))
		return (-1);
	while (!(*n = ft_strchr(*a, '\n')) &&
	((r = read(fd, buf, BUFF_SIZE)) > 0))
	{
		buf[r] = 0;
		temp = *a;
		if (!(*a = ft_strjoin(*a, buf)))
			return (-1);
		ft_strdel(&temp);
	}
	ft_strdel(&buf);
	return (r);
}

int		get_next_line(const int fd, char **line)
{
	//printf("			gnl1\n");
	static char	*a[10240];
	int			r;
	char		*temp;
	char		*n;

	if (fd < 0 || fd > 10240 || !line || (!a[fd] && !(a[fd] = ft_strnew(1)))) {
		return (-1);
	}
	r = read_file(fd, &a[fd], &n);
	if (r == -1 || !(temp = a[fd]))
		ft_strdel(&a[fd]);
	if (r == -1 || !*a[fd])
		return (r == -1 ? -1 : 0);
	if (n)
		*line = ft_strsub(a[fd], 0, n - a[fd]);
	else
	{
		if (!(*line = ft_strdup(a[fd])))
		{
			ft_strdel(&a[fd]);
			return (-1);
		}
	}
	a[fd] = ft_strsub(a[fd], len(*line) + k(n), len(a[fd]) - len(*line) - k(n));
	/*FILE *file = fopen("test.txt", "a");
	fprintf(file, "%s\n", *line);
	fclose(file);
	 */
	ft_strdel(&temp);
	//printf("			gnl2\n");
	return (1);
}