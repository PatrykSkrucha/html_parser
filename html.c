//linked list 

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_list
{
	char *tag;
	struct s_list *next;
}	t_list;

//func list

t_list *init_node(char *tag)
{
	t_list *list = malloc(sizeof(t_list));
	list->tag = tag;
	list->next = NULL;
	return (list);
}


t_list	*lst_last(t_list *lst)
{
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}
void print_lst(t_list *lst)
{
	while(lst)
	{
		printf("%s\n", lst->tag);
		lst = lst->next;
	}
}

void	add_back(t_list **lst, char *tag)
{
	t_list *node = init_node(tag);
	t_list *head = *lst;
	if (*lst == NULL)
	{
		*lst = node;
		return ;
	}
	while ((*lst)->next)
		*lst = (*lst)->next;
	(*lst)->next = node;
	*lst = head;
}

int lst_size(t_list *lst)
{
	int i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	pop_lst(t_list **lst)
{
	if (!lst)
		return ;
	if (lst_size(*lst) == 1)
	{
		*lst = NULL;
		return ;
	}
	t_list *head = *lst;
	while ((*lst)->next)
	{
		if (!(*lst)->next->next)
		{
			(*lst)->next = NULL;
			break;
		}
		else
			(*lst) = (*lst)->next;
	}
	*lst = head;
}

char *get_tag(char *str, int len, int start)
{
	char *str1 = malloc(sizeof(char) * len + 1);
	int i = 0;
	while (i < len)
	{
		str1[i] = str[start + i];
		i++;
	}
	str1[i] = '\0';
	return (str1);
}


//init_node, last_node, add_back, 

int	html_check(char *str)
{
	int i = 0;
	t_list *stack = NULL;
	int start = 0;
	int len = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] != '/')
		{
			start = i + 1;
			while (str[i] != ' ' && str[i] != '>')
				i++;
			len = i - start;
			char *tag = get_tag(str, len, start);
			if (strcmp(tag, "img") != 0)
				add_back(&stack, tag);
		}
		else if (str[i] == '<' && str[i + 1] == '/')
		{
			start = i + 2;
			while (str[i] != '>')
				i++;
			len = i - start;
			char *tag = get_tag(str, len, start);
			if (strcmp(tag, lst_last(stack)->tag) == 0)
				pop_lst(&stack);
			else
				return (1);
		}
		else
			i++;
	}
	return (0);
}

int main(int argc, char **argv)
{

	int i = 1;
	if (argc == 1)
		write(1, "\n", 1);
	else
	{
		while (argv[i])
		{
			if (!html_check(argv[i]))
				write(1, "OK\n", 3);
			else
				write(1, "Error\n", 6);
			i++;
		}
	}
	return (0);
}