/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 01:55:48 by nmina             #+#    #+#             */
/*   Updated: 2025/11/14 12:35:59 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	t_list	*current;

	if (!lst || !f)
		return (NULL);
	new_list = NULL;
	current = lst;
	while (current)
	{
		new_node = ft_lstnew(f(current->content));
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		current = current->next;
	}
	return (new_list);
}

// #include <stdio.h>
// void	*duplicate_content(void *content) {
// 	return ft_strdup((char *)content);
// }
// void	del(void *content) {
// 	free(content);
// }
// int main(){
// 	t_list *head = NULL;
// 	t_list *node1 = ft_lstnew(ft_strdup("Node 1"));
// 	t_list *node2 = ft_lstnew(ft_strdup("Node 2"));
// 	head = node1;
// 	node1->next = node2;
// 	t_list *mapped_list = ft_lstmap(head, duplicate_content, del);
// 	printf("Mapped list contents:\n");
// 	t_list *current = mapped_list;
// 	while (current){
// 		printf("Node content: %s\n", (char *)current->content);
// 		current = current->next;
// 	}
// 	ft_lstclear(&head, del);
// 	ft_lstclear(&mapped_list, del);
// 	return 0;
// }