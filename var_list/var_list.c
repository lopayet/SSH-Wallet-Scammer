/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:11:54 by lopayet-          #+#    #+#             */
/*   Updated: 2023/04/21 13:17:06 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "var_list.h"

t_var_list	*new_var_node(char *name, char *content)
{
	t_var_list	*new;

	new = malloc(sizeof(t_var_list));
	if (!new)
		return (0);
	new->name = name;
	new->content = content;
	new->next = 0;
	return (new);
}

t_var_list	*push_var_node(t_var_list **list, t_var_list *new)
{
	t_var_list	*cursor;

	if (*list == 0)
	{
		new->next = 0;
		*list = new;
		return (new);
	}
	cursor = *list;
	while (cursor->next)
		cursor = cursor->next;
	cursor->next = new;
	new->next = 0;
	return (new);
}

int	modify_var_content(t_var_list *list, char *name, char *content)
{
	t_var_list	*tmp;

	tmp = list;
	while (tmp)
	{
		if (!strcmp(tmp->name, name))
		{
			if (tmp->content)
			{
				free(tmp->content);
				tmp->content = 0;
			}
			if (content)
				tmp->content = strdup(content);
			if (!tmp->content)
				return (-1);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	add_var_node(t_var_list **list, char *name, char *content)
{
	t_var_list	*tmp;
	char		*dupname;
	char		*dupcontent;
	int			res;

	res = modify_var_content(*list, name, content);
	if (res <= 0)
		return (res + 1);
	dupname = strdup(name);
	if (!dupname)
		return (0);
	if (content)
	{
		dupcontent = strdup(content);
		if (!dupcontent)
			return (free(dupname), 0);
	}
	else
		dupcontent = 0;
	tmp = new_var_node(dupname, dupcontent);
	if (!tmp)
		return (0);
	push_var_node(list, tmp);
	return (1);
}

void	free_var_list(t_var_list **list)
{
	t_var_list	*node;
	t_var_list	*next;

	if (*list == 0)
		return ;
	node = *list;
	next = node->next;
	while (next)
	{
		free(node->name);
		if (node->content)
			free(node->content);
		free(node);
		node = next;
		next = node->next;
	}
	free(node->name);
	if (node->content)
		free(node->content);
	free(node);
}
