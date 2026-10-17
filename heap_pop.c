/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_pop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safiraja <safiraja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 09:39:16 by safiraja          #+#    #+#             */
/*   Updated: 2026/10/17 15:42:33 by safiraja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	sift_down(t_heap *h, int i)
{
	int	child;

	while (2 * i + 1 < h->size)
	{
		child = 2 * i + 1;
		if (child + 1 < h->size
			&& heap_less(&h->data[child + 1], &h->data[child]))
			child++;
		if (!heap_less(&h->data[child], &h->data[i]))
			return ;
		heap_swap(&h->data[i], &h->data[child]);
		i = child;
	}
}

t_req	heap_pop(t_heap *h)
{
	t_req	top;

	top = h->data[0];
	h->size--;
	h->data[0] = h->data[h->size];
	sift_down(h, 0);
	return (top);
}
