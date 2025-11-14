/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 01:38:25 by nmina             #+#    #+#             */
/*   Updated: 2025/11/14 11:42:01 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*current;

	count = 0;
	current = lst;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
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
// 	int size = ft_lstsize(head);
// 	printf("List size: %d\n", size); // 3
// 	return 0;
// }