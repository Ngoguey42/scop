/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/02 11:42:05 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/02 11:49:15 by ngoguey          ###   ########.fr       */
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
