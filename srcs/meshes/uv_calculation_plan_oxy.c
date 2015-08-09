/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_calculation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/28 11:41:25 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/09 18:29:05 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
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

static void	fill(t_ftvector *v, float const factoffset[4])
{
	t_vertex_basic				*vertex;
	t_vertex_basic const *const	vertexend = ftv_end(v);

	vertex = v->data;
	while (vertex < vertexend)
	{
		vertex->tex.u = vertex->pos.x * factoffset[0] + factoffset[2];
		vertex->tex.v = vertex->pos.y * factoffset[1] + factoffset[3];
		vertex++;
	}
	return ;
}

void		sp_calc_uv_plan_oxy(t_env const *e, t_mesh const *me
								, t_vbo_basic *vbo)
{
	float			bounds[4];
	float			factoffset[4];
	t_texture const	*t = e->textures + sp_porcelain_texture;
	float const		scale = 1.f;

	lprintf("    Creating some UV coords with plan oxy");
	calc_bounds(&vbo->vertices, bounds, bounds + 2);
	calc_fact_and_offset(bounds, factoffset
					, (float)t->dim[0] / (float)t->dim[1], scale);
	fill(&vbo->vertices, factoffset);
	vbo->ntex = 2;
	return ;
	(void)e;
	(void)me;
}
