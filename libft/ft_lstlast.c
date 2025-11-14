/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 01:41:46 by nmina             #+#    #+#             */
/*   Updated: 2025/11/14 11:46:44 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current->next)
		current = current->next;
	return (current);
}

// #include <stdio.h>
// int main(){
// 	t_list *head = NULL;
// 	t_list *node1 = ft_lstnew("Node 1");
// 	t_list *node2 = ft_lstnew("Node 2");
// 	t_list *node3 = ft_lstnew("Node 3");
// 	head = node1;
// 	node1->next = node2;
// 	node2->next = node3;
// 	t_list *last = ft_lstlast(head);
// 	printf("Last node content: %s\n", (char *)last->content); // Node 3
// 	return 0;
// }