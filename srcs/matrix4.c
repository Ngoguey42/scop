/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/01 14:35:20 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/01 18:00:48 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftmath.h"
#include "ft_debug.h"

#define MULT(A,B,F,G,H,I,M,N,O,P) A[F]*B[M]+A[G]*B[N]+A[H]*B[O]+A[I]*B[P]

const t_matrix4		g_emptym4 =
{
	{0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
		0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f}
};

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

t_matrix4		m4_dotprod(t_matrix4 mata, t_matrix4 matb)
{
	t_matrix4		ret;

	ret.i[0].j[0] = MULT(mata.raw, matb.raw, 0, 1, 2, 3, 0, 4, 8, 12);
	ret.i[0].j[1] = MULT(mata.raw, matb.raw, 0, 1, 2, 3, 1, 5, 9, 13);
	ret.i[0].j[2] = MULT(mata.raw, matb.raw, 0, 1, 2, 3, 2, 6, 10, 14);
	ret.i[0].j[3] = MULT(mata.raw, matb.raw, 0, 1, 2, 3, 3, 7, 11, 15);
	ret.i[1].j[0] = MULT(mata.raw, matb.raw, 4, 5, 6, 7, 0, 4, 8, 12);
	ret.i[1].j[1] = MULT(mata.raw, matb.raw, 4, 5, 6, 7, 1, 5, 9, 13);
	ret.i[1].j[2] = MULT(mata.raw, matb.raw, 4, 5, 6, 7, 2, 6, 10, 14);
	ret.i[1].j[3] = MULT(mata.raw, matb.raw, 4, 5, 6, 7, 3, 7, 11, 15);
	ret.i[2].j[0] = MULT(mata.raw, matb.raw, 8, 9, 10, 11, 0, 4, 8, 12);
	ret.i[2].j[1] = MULT(mata.raw, matb.raw, 8, 9, 10, 11, 1, 5, 9, 13);
	ret.i[2].j[2] = MULT(mata.raw, matb.raw, 8, 9, 10, 11, 2, 6, 10, 14);
	ret.i[2].j[3] = MULT(mata.raw, matb.raw, 8, 9, 10, 11, 3, 7, 11, 15);
	ret.i[3].j[0] = MULT(mata.raw, matb.raw, 12, 13, 14, 15, 0, 4, 8, 12);
	ret.i[3].j[1] = MULT(mata.raw, matb.raw, 12, 13, 14, 15, 1, 5, 9, 13);
	ret.i[3].j[2] = MULT(mata.raw, matb.raw, 12, 13, 14, 15, 2, 6, 10, 14);
	ret.i[3].j[3] = MULT(mata.raw, matb.raw, 12, 13, 14, 15, 3, 7, 11, 15);
	return (ret);
}

#undef MULT
