/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safiraja <safiraja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 09:39:16 by safiraja          #+#    #+#             */
/*   Updated: 2026/10/17 15:42:32 by safiraja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	heap_less(const t_req *a, const t_req *b)
{
	if (a->key != b->key)
		return (a->key < b->key);
	return (a->coder_id < b->coder_id);
}

void	heap_swap(t_req *a, t_req *b)
{
	t_req	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	heap_push(t_heap *h, t_req r)
{
	int	i;

	if (h->size >= h->cap)
		return (-1);
	i = h->size;
	h->data[i] = r;
	h->size++;
	while (i > 0 && heap_less(&h->data[i], &h->data[(i - 1) / 2]))
	{
		heap_swap(&h->data[i], &h->data[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
	return (0);
}

const t_req	*heap_peek(const t_heap *h)
{
	if (h->size == 0)
		return (NULL);
	return (&h->data[0]);
}
