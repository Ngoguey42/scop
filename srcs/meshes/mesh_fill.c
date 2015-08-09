/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/09 14:15:56 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/09 18:27:58 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <string.h>

#define NORM_AT_42_IS_WTF(E, ME, RVBO) (ME)->fill((E), (ME), (RVBO))

static t_locations_backup_fill const	g_backup_fill[] = {
	{offsetof(t_vbo_basic, npos), NULL},
	{offsetof(t_vbo_basic, ncol), NULL},
	{offsetof(t_vbo_basic, ntex), NULL},
	{offsetof(t_vbo_basic, nnor), NULL},
};

#define TAB_SIZE (sizeof(g_vbo_basic_offsets) / sizeof(*g_vbo_basic_offsets))

static int		fill_gab(t_env const *e, t_mesh const *me
							, t_vbo_basic raw_vbo[1])
{
	t_vshader const *const	vshader = VSOFME(e, me);
	t_location const		*loc = vshader->locations;
	t_location const *const	locend = loc + vshader->n_locations;
	t_byte					s_cur;
	t_byte					s_wished;

	while (loc < locend)
	{
		s_cur = *(t_byte*)((void*)raw_vbo + g_backup_fill[loc->type].noff);
		s_wished = loc->size;
		if (s_cur != s_wished)
			ERRORF("s_cur == %hhu/%hhu", s_cur, s_wished);
		loc++;
	}
	return (0);
}

static void		shrink_vbo(t_ftvector *const dst, t_vbo_basic const *const srcb)
{
	t_ftvector const *const			srcv = &srcb->vertices;
	t_vertex_basic const			*src = srcv->data;
	t_vertex_basic const *const		srcend = ftv_end(srcv);
	float							tmp[dst->chunk_size / sizeof(float)];
	float							*tmpptr;

	if (ftv_reserve(dst, srcv->size))
		sp_enomem();
	while (src < srcend)
	{
		tmpptr = tmp;
		if (srcb->npos > 0)
		{
			memcpy(tmpptr, &src->pos, srcb->npos * sizeof(float));
			tmpptr += srcb->npos;
		}
		if (srcb->ncol > 0)
		{
			memcpy(tmpptr, &src->col, srcb->ncol * sizeof(float));
			tmpptr += srcb->ncol;
		}
		if (srcb->ntex > 0)
		{
			memcpy(tmpptr, &src->tex, srcb->ntex * sizeof(float));
			tmpptr += srcb->ntex;
		}
		if (srcb->nnor > 0)
		{
			memcpy(tmpptr, &src->nor, srcb->nnor * sizeof(float));
			tmpptr += srcb->nnor;
		}
		ftv_push_back_unsafe(dst, tmp);
		src++;
	}
	return ;
}

int				sp_fill_mesh(t_env const *e, t_mesh *me)
{
	t_vbo_basic		raw_vbo[1];

	bzero(raw_vbo, sizeof(t_vbo_basic));
	ftv_init_instance(&raw_vbo->vertices, sizeof(t_vertex_basic));
	if (NORM_AT_42_IS_WTF(e, me, raw_vbo))
		return (ERROR("me->fill(e, me)"), 1);
	fill_gab(e, me, raw_vbo);
	shrink_vbo(&me->vertices, raw_vbo);
	ftv_release(&raw_vbo->vertices, NULL);
	return (0);
}
