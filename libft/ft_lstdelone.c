/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 01:47:44 by nmina             #+#    #+#             */
/*   Updated: 2025/11/14 12:22:56 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

// #include <stdio.h>
// void del(void *content) {
// 	free(content);
// }
// int main(){
// 	t_list *node = ft_lstnew(ft_strdup("hi"));
// 	printf("Before deletion: %s\n", (char *)node->content);
// 	ft_lstdelone(node, del);
// 	printf("Node deleted.\n");
// 	return 0;
// }