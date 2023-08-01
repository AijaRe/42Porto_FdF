/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 08:11:37 by arepsa            #+#    #+#             */
/*   Updated: 2023/04/26 14:40:32 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*lst - the node to free*/
/*frees the memory of the node’s content..*/
/*..using the function ’del’ given as a parameter..*/
/*..and free the node. The memory of ’next’ must not be freed.*/
/*(lst->content implicitly cast to void*)*/
void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	(*del)(lst->content);
	free(lst);
}
