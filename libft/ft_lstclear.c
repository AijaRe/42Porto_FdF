/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 08:38:35 by arepsa            #+#    #+#             */
/*   Updated: 2023/04/26 14:41:59 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Deletes and frees the given node and every successor
 of that node, using the function ’del’ and free.
The pointer to the list must be set to NULL*/
/*lst - address of a pointer to a node.
del - address of the function used to delete
the content of the node*/
/* *lst = curr->next : update lst to point to the next node*/
/* curr = *lst : update curr to point to the next node*/
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*curr;

	if (!lst)
		return ;
	curr = *lst;
	while (curr)
	{
		*lst = curr->next;
		(*del)(curr->content);
		free(curr);
		curr = *lst;
	}
	*lst = NULL;
}
