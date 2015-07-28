/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_calculation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/28 11:41:25 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/28 11:41:40 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <assert.h>
#include "scop.h"

static void	calc_bounds(float const *vert, size_t nvert,
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

static void	fill(t_ftvector *new, t_ftvector const *old, float fact[2])
{
	float const	*ptr = old->data;
	float const *end = ftv_end(old);
	float		tmp[5];

	while (ptr < end)
	{
		memcpy(tmp, ptr, sizeof(*tmp) * 3);
		tmp[3] = ptr[0] * fact[0];
		tmp[4] = ptr[1] * fact[1];
		ftv_push_back_unsafe(new, tmp);
		ptr += 3;
	}
	return ;
}

void		sp_wrap_texture_planxy(t_ftvector *v, float scale, float imgratio)
{
	t_ftvector		newv[1];

	assert(v->chunk_size == 3 * sizeof(float));
	ftv_init_instance(newv, sizeof(float) * 5);
	ftv_reserve(newv, v->size);
	fill(newv, v, (float[2]){1 / (scale * imgratio), 1 / scale});
	ftv_release(v, NULL);
	*v = *newv;
	(void)calc_bounds;
	return ;
}
