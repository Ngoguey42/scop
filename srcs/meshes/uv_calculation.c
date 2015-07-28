/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_calculation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/28 11:41:25 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/28 15:00:54 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <assert.h>
#include "scop.h"

static void	calc_bounds(t_ftvector const *const v, float bx[2], float by[2])
{
	float const			*vertex = v->data;
	float const *const	vertexend = ftv_end(v);
	size_t const		num_floats = v->chunk_size / sizeof(float);

	bx[0] = vertex[0];
	bx[1] = vertex[0];
	by[0] = vertex[1];
	by[1] = vertex[1];
	vertex += num_floats;
	while (vertex < vertexend)
	{
		if (*vertex < bx[0])
			bx[0] = *vertex;
		else if (*vertex > bx[1])
			bx[1] = *vertex;
		vertex++;
		if (*vertex < by[0])
			by[0] = *vertex;
		else if (*vertex > by[1])
			by[1] = *vertex;
		vertex += num_floats - 1;
	}
	return ;
}

static void	fill(t_ftvector *const new, t_ftvector const *oldv,
				 float const fact[2], float const offsets[2],
				 size_t const padfloats)
{
	float const			*vertex = oldv->data;
	float const *const	vertexend = ftv_end(oldv);
	size_t const		old_num_floats = oldv->chunk_size / sizeof(float);
	float				tmp[old_num_floats + 2];

	while (vertex < vertexend)
	{
		memcpy(tmp, vertex, padfloats * sizeof(float));
		memcpy(tmp, vertex + (padfloats + 2) * sizeof(float)
			   , oldv->chunk_size - padfloats * sizeof(float));
		tmp[padfloats] = vertex[0] * fact[0] + offsets[0];
		tmp[padfloats + 1] = vertex[1] * fact[1] + offsets[1];
		ftv_push_back_unsafe(new, tmp);
		vertex += old_num_floats;
	}
	return ;
}

void		sp_wrap_texture_planxy(t_ftvector *v, t_texture const *t,
									float scale, size_t padfloats)
{
	t_ftvector		newv[1];
	float const		imgratio = (float)t->dim[0] / (float)t->dim[1];
	float			bx[2];
	float			by[2];
	float			dx;
	float			dy;

	float			obratio;
	
	float			fact[2];
	float			offsets[2];
	
	lprintf("    Creating some UV coords");
	assert(v->chunk_size == 3 * sizeof(float));
	if (ftv_init_instance(newv, sizeof(float) * 5)
		|| ftv_reserve(newv, v->size))
		sp_enomem();
	calc_bounds(v, bx, by);
	dx = bx[1] - bx[0];
	dy = by[1] - by[0];


	obratio = dx / dy;
	
	fact[0] = 1 / (dx) * scale;
	fact[1] = 1 / (dy) * scale;

	offsets[0] = -bx[0] * fact[0];
	offsets[1] = -by[0] * fact[1];
	
	qprintf("imgratio %f\n", imgratio);
	qprintf("obratio %f\n", obratio);

	if (imgratio > obratio)
	{
		/* float	correction; */
		/* //todo */
		/* correction = (imgratio - obratio) / imgratio; */
		/* fact[0] *= (1 - correction); */
		/* offsets[0] += correction / 2 * (-bx[0] * fact[0]); */
		fact[0] *= 1 / (imgratio / obratio);
		offsets[0] += 1 / (imgratio / obratio) / 2;
	}
	else
	{
		fact[1] *= imgratio / obratio;
		offsets[1] = -by[0] * fact[1];
		/* offsets[1] = -by[0] * fact[1] + (obratio - imgratio) / (obratio * 2); */
	}
	
	fill(newv, v, fact
		 , offsets
		 , padfloats);
	/* fill(newv, v, (float[2]){1 / (scale * imgratio), 1 / scale}, padfloats); */
	ftv_release(v, NULL);
	*v = *newv;
	(void)calc_bounds;
	(void)scale;
	(void)imgratio;
	return ;
}
