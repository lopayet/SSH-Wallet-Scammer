/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list_fn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:09:58 by lopayet-          #+#    #+#             */
/*   Updated: 2023/04/21 14:57:41 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "var_list.h"

static char	*dup_variable_name(char *var)
{
	int		i;
	char	*dup;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	dup = malloc(i + 1);
	if (!dup)
		return (0);
	i = 0;
	while (var[i] && var[i] != '=')
	{
		dup[i] = var[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

static char	*dup_variable_content(char *var)
{
	int		i;
	int		start;
	char	*dup;

	start = 0;
	while (var[start] && var[start] != '=')
		start++;
	start++;
	i = start;
	while (var[i])
		i++;
	dup = malloc(i - start + 1);
	if (!dup)
		return (0);
	i = 0;
	while (var[i + start])
	{
		dup[i] = var[i + start];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

t_var_list	*get_var_list_from_envp(char **envp)
{
	t_var_list	*list;
	t_var_list	*new;

	list = 0;
	while (*envp)
	{
		new = new_var_node(dup_variable_name(*envp),
				dup_variable_content(*envp));
		push_var_node(&list, new);
		envp++;
	}
	return (list);
}

char	*get_var_content(t_var_list *list, char *name)
{
	t_var_list	*node;

	if (list == 0)
		return (0);
	node = list;
	while (node)
	{
		if (strcmp(node->name, name) == 0)
			return (node->content);
		node = node->next;
	}
	return (0);
}

char	*dup_var_content(t_var_list *list, char *name)
{
	char	*content;

	content = get_var_content(list, name);
	if (!content)
		return (NULL);
	return (strdup(content));
}
