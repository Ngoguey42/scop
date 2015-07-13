/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/02 11:42:05 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/13 16:17:18 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftmath.h"
#include <math.h>

extern t_matrix4    g_identitym4;

t_matrix4	m4_fovprojection(float fov, float ratio, float near, float far)
{
	float const		frustumDepth = far - near;
	float const		oneOverDepth = 1 / frustumDepth;
	t_matrix4		result;

	result = g_identitym4;
	result.i[1].j[1] = 1 / tan(0.5f * fov);
	result.i[0].j[0] = 1 * result.i[1].j[1] / ratio;
	result.i[2].j[2] = -far * oneOverDepth;
	result.i[2].j[3] = (-far * near) * oneOverDepth * 2;
	result.i[3].j[2] = -1;
	result.i[3].j[3] = 0;
	return (result);
}

t_matrix4	m4_lookat(t_vector3 eye, t_vector3 at)
{
	t_vector3 const		up = (t_vector3){0.f, 1.f, 0.f};
	t_vector3 const		z = v3_normalize(v3_sub(eye, at));
	t_vector3 const		x = v3_normalize(v3_cross(up, z));
	t_vector3 const		y = v3_cross(z, x);

	return ((t_matrix4)
		{
			x.x, x.y, x.z, -(x.x * eye.x + x.y * eye.y + x.z * eye.z),
				y.x, y.y,y.z,-(y.x * eye.x + y.y * eye.y + y.z * eye.z),
				z.x,z.y,z.z,-(z.x * eye.x + z.y * eye.y + z.z * eye.z),
				0, 0, 0, 1});
}
