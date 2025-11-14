/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 01:51:33 by nmina             #+#    #+#             */
/*   Updated: 2025/11/14 12:25:07 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next_node;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current)
	{
		next_node = current->next;
		del(current->content);
		free(current);
		current = next_node;
	}
	*lst = NULL;
}

// #include <stdio.h>
// void del(void *content) {
// 	free(content);
// }
// int main(){
// 	t_list *head = NULL;
// 	t_list *node1 = ft_lstnew(ft_strdup("Node 1"));
// 	t_list *node2 = ft_lstnew(ft_strdup("Node 2"));
// 	head = node1;
// 	node1->next = node2;
// 	printf("Before clearing list:\n");
// 	t_list *current = head;
// 	while (current){
// 		printf("Node content: %s\n", (char *)current->content);
// 		current = current->next;
// 	}	
// 	ft_lstclear(&head, del);
// 	printf("List cleared successfully.\n");
// 	return 0;
// }