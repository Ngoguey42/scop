/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_xy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/18 10:52:20 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/18 11:58:55 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "texture_mapping.h"

static void		calc_bounds(float const *vert, size_t nvert,
							float bx[2], float by[2])
{
	float const	*v;

	bx[0] = vert[0];
	bx[1] = vert[0];
	by[0] = vert[1];
	by[1] = vert[1];
	v = vert + 3;
	while (nvert-- > 1)
	{
		if (*v < bx[0])
			bx[0] = *v;
		else if (*v > bx[1])
			bx[1] = *v;
		v += 1;
		if (*v < by[0])
			by[0] = *v;
		else if (*v > by[1])
			by[1] = *v;
		v += 2;
	}
	return ;
}

static void		fill(t_ftvector *new, t_ftvector const *old, float fact[2])
{
	float const	*ptr = old->data;
	float const *end = ((float*)old->data) + old->size;
	float		tmp[1];

	while (ptr < end)
	{
		ftv_push_backn(new, ptr, 3);
		*tmp = ptr[0] * fact[0];
		ftv_push_back(new, tmp);
		*tmp = ptr[1] * fact[1];
		ftv_push_back(new, tmp);
		ptr += 3;
	}
	return ;
}

void	sp_wrap_texture_planxy(t_objmodel *m, float scale, float imgratio)
{
	t_ftvector		newv[1];

	ftv_init_instance(newv, sizeof(float) * 5);
	ftv_reserve(newv, m->vertices.size / 3 * 5);

	/* 0.f / 0.f =>	0.f / 0.f; */

	/* scale 1.f, ratio 1.5f; */
	/* 1.f / 0.f =>	0.66f / 0.f; */
	/* 0.f / 1.f =>	0.f   / 1.f; */
	

	
	/* 3.0 / 2.0; */

	
	
	/* 1.f / scale */

	
	fill(newv, &m->vertices, (float[2]){1 / (scale * imgratio), 1 / scale});
	/* float   boundsx[2]; */
	/* float   boundsy[2]; */
	/* float	objratio; */
	/* float	 */
	
	/* calc_bounds(m->vertices.data, m->vertices.size, boundsx, boundsy); */
	/* objratio = (boundsx[1] - boundsx[0]) / (boundsy[1] - boundsy[0]); */
	/* qprintf("Found: %u vert\n", m->vertices.size); */
	/* qprintf("Found: %f ratio vs %f\n", imgratio, objratio); */
	/* qprintf("Found: x: %f -> %f\n", boundsx[0], boundsx[1]); */
	/* qprintf("Found: y: %f -> %f\n", boundsy[0], boundsy[1]); */
	/* qprintf("midx = %f\n", boundsx[0] / 2 + boundsx[1] / 2); */
	/* qprintf("midy = %f\n", boundsy[0] / 2 + boundsy[1] / 2); */
	
	
	return ;
}
