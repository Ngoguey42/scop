/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4_miscop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 10:07:41 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/20 12:22:19 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftmath.h"
#include <math.h>

extern t_matrix4	g_identitym4;

#define MULT(A,B,F,G,H,I,M,N,O,P) A[F]*B[M]+A[G]*B[N]+A[H]*B[O]+A[I]*B[P]

#define LAI0 x.x, x.y, x.z, -(x.x * eye.x + x.y * eye.y + x.z * eye.z)
#define LAI1 y.x, y.y, y.z, -(y.x * eye.x + y.y * eye.y + y.z * eye.z)
#define LAI2 z.x, z.y, z.z, -(z.x * eye.x + z.y * eye.y + z.z * eye.z)
#define LAI3 0, 0, 0, 1

t_matrix4	m4_dotprod(t_matrix4 const *mata, t_matrix4 const *matb)
{
	t_matrix4	ret;

	ret.i[0].j[0] = MULT(mata->raw, matb->raw, 0, 1, 2, 3, 0, 4, 8, 12);
	ret.i[0].j[1] = MULT(mata->raw, matb->raw, 0, 1, 2, 3, 1, 5, 9, 13);
	ret.i[0].j[2] = MULT(mata->raw, matb->raw, 0, 1, 2, 3, 2, 6, 10, 14);
	ret.i[0].j[3] = MULT(mata->raw, matb->raw, 0, 1, 2, 3, 3, 7, 11, 15);
	ret.i[1].j[0] = MULT(mata->raw, matb->raw, 4, 5, 6, 7, 0, 4, 8, 12);
	ret.i[1].j[1] = MULT(mata->raw, matb->raw, 4, 5, 6, 7, 1, 5, 9, 13);
	ret.i[1].j[2] = MULT(mata->raw, matb->raw, 4, 5, 6, 7, 2, 6, 10, 14);
	ret.i[1].j[3] = MULT(mata->raw, matb->raw, 4, 5, 6, 7, 3, 7, 11, 15);
	ret.i[2].j[0] = MULT(mata->raw, matb->raw, 8, 9, 10, 11, 0, 4, 8, 12);
	ret.i[2].j[1] = MULT(mata->raw, matb->raw, 8, 9, 10, 11, 1, 5, 9, 13);
	ret.i[2].j[2] = MULT(mata->raw, matb->raw, 8, 9, 10, 11, 2, 6, 10, 14);
	ret.i[2].j[3] = MULT(mata->raw, matb->raw, 8, 9, 10, 11, 3, 7, 11, 15);
	ret.i[3].j[0] = MULT(mata->raw, matb->raw, 12, 13, 14, 15, 0, 4, 8, 12);
	ret.i[3].j[1] = MULT(mata->raw, matb->raw, 12, 13, 14, 15, 1, 5, 9, 13);
	ret.i[3].j[2] = MULT(mata->raw, matb->raw, 12, 13, 14, 15, 2, 6, 10, 14);
	ret.i[3].j[3] = MULT(mata->raw, matb->raw, 12, 13, 14, 15, 3, 7, 11, 15);
	return (ret);
}

t_matrix4	m4_lookat(t_vector3 eye, t_vector3 at)
{
	t_vector3 const		up = (t_vector3){0.f, 1.f, 0.f};
	t_vector3 const		z = v3_normalize(v3_sub(eye, at));
	t_vector3 const		x = v3_normalize(v3_cross(up, z));
	t_vector3 const		y = v3_cross(z, x);

	return (ATOM4(LAI0, LAI1, LAI2, LAI3));
}

t_matrix4	m4_fovprojection(float fov, float ratio, float near, float far)
{
	float const		one_over_depth = 1.f / (far - near);
	t_matrix4		result;

	result = g_identitym4;
	result.i[1].j[1] = 1.f / tan(0.5f * fov);
	result.i[0].j[0] = 1.f * result.i[1].j[1] / ratio;
	result.i[2].j[2] = -far * one_over_depth;
	result.i[2].j[3] = (-far * near) * one_over_depth * 2.f;
	result.i[3].j[2] = -1.f;
	result.i[3].j[3] = 0;
	return (result);
}
