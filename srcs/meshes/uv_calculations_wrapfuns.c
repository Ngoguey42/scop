/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_calculations_wrapfuns.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/24 17:27:15 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/24 17:29:48 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <math.h>
#include "scop.h"

#define STEP 0.1f
#define ANGLE_BETWEEN(V1, V2) (acos(v3_dot_normed((V1), (V2))))

static float	process_angle(float a)
{
	if (a < 0)
		return (-a);
	return (a);
}

void			sp_calc_uv_spherical(t_vertex_basic *vertex
									, float const factoffset[4])
{
	t_vector3					tmp;

	tmp = *(t_vector3*)&vertex->pos;
	if (ABS(tmp.x) < STEP && ABS(tmp.z) < STEP)
	{
		tmp.x = STEP;
		tmp.z = STEP;
	}
	vertex->tex.u = process_angle(atan(tmp.x / tmp.z))
		* factoffset[0] + factoffset[2];
	vertex->tex.v = acos(tmp.y / sqrt(tmp.x * tmp.x
									+ tmp.y * tmp.y
									+ tmp.z * tmp.z))
		* factoffset[1] + factoffset[3];
	return ;
}

void			sp_calc_uv_planaroxy(t_vertex_basic *vertex
									, float const factoffset[4])
{
	vertex->tex.u = vertex->pos.x * factoffset[0] + factoffset[2];
	vertex->tex.v = vertex->pos.y * factoffset[1] + factoffset[3];
	return ;
}

void			sp_calc_uv_box(t_vertex_basic *vertex
								, float const factoffset[4])
{
	float	const	nx = ABS(vertex->nor.x);
	float	const	ny = ABS(vertex->nor.y);
	float	const	nz = ABS(vertex->nor.z);

	if (nz > nx && nz > ny)
	{
		vertex->tex.u = ABS(vertex->pos.x) * factoffset[0] + factoffset[2];
		vertex->tex.v = ABS(vertex->pos.y) * factoffset[1] + factoffset[3];
	}
	else if (ny > nx)
	{
		vertex->tex.u = ABS(vertex->pos.x) * factoffset[0] + factoffset[2];
		vertex->tex.v = -ABS(vertex->pos.z) * factoffset[1] + factoffset[3];
	}
	else
	{
		vertex->tex.u = -ABS(vertex->pos.z) * factoffset[0] + factoffset[2];
		vertex->tex.v = ABS(vertex->pos.y) * factoffset[1] + factoffset[3];
	}
	return ;
}

void		(*const g_wrapfuns[])() =
{
	&sp_calc_uv_planaroxy,
	&sp_calc_uv_spherical,
	&sp_calc_uv_box,
};
