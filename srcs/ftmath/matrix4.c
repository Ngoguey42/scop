/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/01 14:35:20 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/15 10:09:31 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftmath.h"
#include "ft_debug.h"

#define MULT(A,B,F,G,H,I,M,N,O,P) A[F]*B[M]+A[G]*B[N]+A[H]*B[O]+A[I]*B[P]

const t_matrix4		g_identitym4 =
{
	{1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f}
};

void			m4_print(t_matrix4 mat)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if (i % 4 == 3)
			qprintf("% 5.2f\n", mat.raw[i]);
		else
			qprintf("% 5.2f, ", mat.raw[i]);
		i++;
	}
	return ;
}
