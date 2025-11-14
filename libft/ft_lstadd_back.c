/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 01:44:11 by nmina             #+#    #+#             */
/*   Updated: 2025/11/14 12:04:34 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

// #include <stdio.h>
// int main(){
// 	t_list *head = NULL;
// 	t_list *node1 = ft_lstnew("Node 1");
// 	t_list *node2 = ft_lstnew("Node 2");
// 	ft_lstadd_back(&head, node1);
// 	ft_lstadd_back(&head, node2);
// 	t_list *current = head;
// 	while (current){
// 		printf("Node content: %s\n", (char *)current->content);
// 		current = current->next;
// 	}
// 	return 0;
// }