/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 15:45:29 by tcollard          #+#    #+#             */
/*   Updated: 2018/01/19 11:34:44 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft/includes/libft.h"

# define BUFF_SIZE 5

typedef struct			s_gnl
{
	int					fd;
	int					ret_read;
	char				*data;
	struct s_gnl		*next;
}						t_gnl;
int						get_next_line(const int fd, char **line);
int						fill_line(t_gnl *lst, char **line, char *tmp);
int						read_fd(t_gnl *lst, char **line);

#endif
