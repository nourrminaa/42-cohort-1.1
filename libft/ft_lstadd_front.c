/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 01:35:47 by nmina             #+#    #+#             */
/*   Updated: 2025/11/14 11:40:11 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

// #include <stdio.h>
// int main(){
// 	t_list *head = NULL;
// 	t_list *new_node = ft_lstnew("First Node");
// 	t_list *new_node2 = ft_lstnew("New Head Node");
// 	ft_lstadd_front(&head, new_node);
// 	ft_lstadd_front(&head, new_node2);

// 	t_list *current = head;
// 	while (current){
// 		printf("Node content: %s\n", (char *)current->content);
// 		current = current->next;
// 	}
// 	return 0;
// }