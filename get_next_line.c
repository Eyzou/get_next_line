/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:34:19 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/16 17:54:30 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	add_new_node(t_list **list, char *tmp)
{
	t_list	*new_node;
	t_list	*last;

	last = ft_lst_last(*list);
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	if (last == NULL)
		*list = new_node;
	else
		last->next = new_node;
	new_node->content = tmp;
	new_node->next = NULL;
}

static void	read_and_stock_line(t_list **list, int fd)
{
	char	*tmp;
	int		char_count;

	while (find_new_line(*list) == 0)
	{
		tmp = malloc(BUFFER_SIZE + 1);
		if (tmp == NULL)
			return ;
		char_count = read(fd, tmp, BUFFER_SIZE);
		if (char_count <= 0)
			return (free(tmp));
		tmp[char_count] = '\0';
		add_new_node(list, tmp);
	}
}

static char	*extract_from_list_to_line(t_list *list)
{
	int		len;
	char	*line;

	if (list == NULL)
		return (NULL);
	len = len_to_new_line(list);
	line = malloc(len + 1);
	if (line == NULL)
		return (NULL);
	copy(list, line);
	return (line);
}

static void	remaining_list(t_list **list)
{
	t_list	*last_node;
	t_list	*new_node;
	int		i;
	int		k;
	char	*buf;

	i = 0;
	k = 0;
	buf = malloc(BUFFER_SIZE + 1);
	new_node = malloc(sizeof(t_list));
	last_node = ft_lst_last(*list);
	while (last_node->content[i] && last_node->content[i] != '\n')
		++i;
	while (last_node->content[i] && last_node->content[++i])
		buf[k++] = last_node->content[i];
	buf[k] = '\0';
	new_node->content = buf;
	new_node->next = NULL;
	free_list(list, new_node, buf);
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_and_stock_line(&list, fd);
	if (list == NULL)
		return (NULL);
	line = extract_from_list_to_line(list);
	remaining_list(&list);
	return (line);
}

/*int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		printf("%s", line);
		if (line == NULL)
			break ;
		free(line);
	}
	close(fd);
	return (0);
}*/
