/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objmodel_retreive.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/12 17:06:35 by ngoguey           #+#    #+#             */
/*   Updated: 2015/09/03 11:42:07 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "scop.h"
#include "objmodel/objmodel_parsing.h"
#include "ft_containers.h"

static void	push_index(size_t const *ptrpad, void *beginptr, int i)
{
	*(t_ui*)(beginptr + *ptrpad) = (t_ui)i;
	return ;
}

static void	build_faces(void **ptrs, t_tmpface const *face)
{
	t_ui			tmp[3];
	size_t const	ptrpad = *(size_t*)ptrs[1];

	tmp[0] = *(t_ui*)((void*)face->ptr[0] + ptrpad);
	tmp[1] = *(t_ui*)((void*)face->ptr[1] + ptrpad);
	tmp[2] = *(t_ui*)((void*)face->ptr[2] + ptrpad);
	ftv_push_back_unsafe(ptrs[0], tmp);
	return ;
}

static void	retreive_faces(t_objmodel const *const m, t_ftvector *const f)
{
	void	*ptrs[2];
	size_t	padtoindex;

	if (ftv_reserve(f, m->faces.size))
		sp_enomem();
	padtoindex = m->vertices.chunk_size - sizeof(t_ui);
	ptrs[0] = f;
	ptrs[1] = &padtoindex;
	ftv_foreach(&m->faces, &build_faces, ptrs);
	return ;
}

static void	extract_vertices(t_vertex_basic *dst, void const *src
								, t_ui const nfloats[1])
{
	float	*floats;

	floats = (float*)(src + sizeof(t_ftset_node));
	memcpy(&dst->pos, floats + 0, sizeof(float) * 3);
	if (*nfloats == 5 || *nfloats == 8)
		memcpy(&dst->tex, floats + 3, sizeof(float) * 2);
	if (*nfloats == 6)
		memcpy(&dst->nor, floats + 3, sizeof(float) * 3);
	else if (*nfloats == 8)
		memcpy(&dst->nor, floats + 5, sizeof(float) * 3);
	return ;
}

void		op_retreive_data(t_objmodel *m, t_vbo_basic *v, t_ftvector *f)
{
	size_t		ptrpad;
	t_ui		nfloats[1];

	ptrpad = m->width * sizeof(float) + sizeof(t_ftset_node);
	v->npos = 3;
	if (m->width == 5 || m->width == 8)
		v->ntex = 2;
	if (m->width == 6 || m->width == 8)
		v->nnor = 3;
	fts_foreachi(&m->vertices, &push_index, &ptrpad);
	retreive_faces(m, f);
	*nfloats = (m->vertices.chunk_size - sizeof(t_ui) - sizeof(t_ftset_node))
				/ sizeof(float);
	ft_set_to_vector(&m->vertices, &v->vertices, &extract_vertices, nfloats);
	return ;
}
