/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:07:17 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/16 18:00:58 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

t_list			*ft_lst_last(t_list *lst);
int				find_new_line(t_list *list);
void			copy(t_list *list, char *dest);
int				len_to_new_line(t_list *list);
void			free_list(t_list **list, t_list *new_node, char *buf);
char			*get_next_line(int fd);

#endif
