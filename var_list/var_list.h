
#ifndef VAR_LIST_H
# define VAR_LIST_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_var_list	t_var_list;
struct s_var_list
{
	char		*name;
	char		*content;
	t_var_list	*next;
};

int			modify_var_content(t_var_list *list, char *name, char *content);
t_var_list	*get_var_list_from_envp(char **envp);
t_var_list	*push_var_node(t_var_list **list, t_var_list *new);
int			add_var_node(t_var_list **list, char *name, char *content);
t_var_list	*new_var_node(char *name, char *content);
void		free_var_list(t_var_list **list);
// fn
char		*get_var_content(t_var_list *list, char *name);
char		*dup_var_content(t_var_list *list, char *name);

// utils
int			list_len(t_var_list *list);
char		**list_to_char(t_var_list *list);
void		remove_var_node(t_var_list **list, char *name);

#endif
