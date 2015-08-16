/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_calculations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/15 11:15:10 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/16 18:26:59 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <math.h>
#include <assert.h>
#include "scop.h"

/*
** bounds[0]		-> boundx min (left)
** bounds[1]		-> boundx max (right)
** bounds[2]		-> boundy min (bottom)
** bounds[3]		-> boundy max (top)
** *
** factoffset[0]	-> factorX
** factoffset[1]	-> factorY
** factoffset[2]	-> offsetX
** factoffset[3]	-> offsetY
** *
** 'calc_fact_and_offset':
** 'if (imgratio < obratio)'
** |		scale 1 will match image's left right bounds
** |	'factoffset[1] *= imgratio / obratio'
** |		decreases the factorY to match image's ratio
** |	'factoffset[3] = -bounds[2] * factoffset[1]'
** |		increases the offsetY (might be useless)
** |	Use this when for centered textures:
** |	factoffset[3] = -by[0] * factoffset[1]
** |					+ (obratio - imgratio) / (obratio * 2);
*/
#define STEP 0.1f
#define ANGLE_BETWEEN(V1, V2) (acos(v3_dot_normed((V1), (V2))))

static void	calc_fact_and_offset(float const bounds[4], float factoffset[4],
									float const imgratio, float const scale)
{
	float			dx;
	float			dy;
	float			obratio;

	dx = bounds[1] - bounds[0];
	dy = bounds[3] - bounds[2];
	obratio = dx / dy;
	factoffset[0] = scale / dx;
	factoffset[1] = scale / dy;
	factoffset[2] = -bounds[0] * factoffset[0];
	factoffset[3] = -bounds[2] * factoffset[1];
	if (imgratio > obratio)
	{
		factoffset[0] /= imgratio / obratio;
		factoffset[2] = -bounds[0] * factoffset[0];
	}
	else
	{
		factoffset[1] *= imgratio / obratio;
		factoffset[3] = -bounds[2] * factoffset[1];
	}
	return ;
}

static void	calc_bounds(t_ftvector const *const v, float bx[2], float by[2])
{
	t_vertex_basic const		*vertex = v->data;
	t_vertex_basic const *const	vertexend = ftv_end(v);

	bx[0] = vertex->pos.x;
	bx[1] = vertex->pos.x;
	by[0] = vertex->pos.y;
	by[1] = vertex->pos.y;
	while (vertex < vertexend)
	{
		if (vertex->pos.x < bx[0])
			bx[0] = vertex->pos.x;
		else if (vertex->pos.x > bx[1])
			bx[1] = vertex->pos.x;
		if (vertex->pos.y < by[0])
			by[0] = vertex->pos.y;
		else if (vertex->pos.y > by[1])
			by[1] = vertex->pos.y;
		vertex++;
	}
	return ;
}

static float	process_angle(float a)
{
	if (a < 0)
		return (-a);
	return (a);
}

void		sp_calc_uv_spherical(t_vertex_basic *vertex
								 , float const factoffset[4])
{
	t_vector3					tmp;

	tmp = *(t_vector3*)&vertex->pos;
	if (ABS(tmp.x) < STEP && ABS(tmp.z) < STEP)
		tmp.x = tmp.z = STEP;
	vertex->tex.u = process_angle(atan(tmp.x / tmp.z))
		* factoffset[0] + factoffset[2];
	vertex->tex.v = acos(tmp.y / sqrt(tmp.x * tmp.x
									  + tmp.y * tmp.y
									  + tmp.z * tmp.z))
		* factoffset[1] + factoffset[3];
	return ;
}



void		sp_calc_uv_planaroxy(t_vertex_basic *vertex
								 , float const factoffset[4])
{
	vertex->tex.u = vertex->pos.x * factoffset[0] + factoffset[2];
	vertex->tex.v = vertex->pos.y * factoffset[1] + factoffset[3];
	return ;
}

void		sp_calc_uv_box(t_vertex_basic *vertex
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

static void	(*const g_wrapfuns[])() =
{
	&sp_calc_uv_planaroxy,
	&sp_calc_uv_spherical,
	&sp_calc_uv_box,
};

static void	fill(t_ftvector *v, float const factoffset[4], void (*fun)())
{
	t_vertex_basic				*vertex;
	t_vertex_basic const *const	vertexend = ftv_end(v);

	vertex = v->data;
	while (vertex < vertexend)
		fun(vertex++, factoffset);
	return ;
}

void		sp_calc_uv(t_env const *e, t_vbo_basic *vbo, float d[2]
								, t_uvwrapping_type t)
{
	float			bounds[4];
	float			factoffset[4];	

	lprintf("    Creating some UV coords with plan oxy");
	calc_bounds(&vbo->vertices, bounds, bounds + 2);
	calc_fact_and_offset(bounds, factoffset, d[0], d[1]);
	fill(&vbo->vertices, factoffset, g_wrapfuns[t]);
	vbo->ntex = 2;
	return ;
	(void)e;
}
