/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objmodel_swap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/09 15:05:18 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/12 15:12:55 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "scop.h"
#include "objmodel_parsing.h"

static void	retreive_vertices(t_objmodel const *const m, t_ftvector *const v)
{
	/* float const			*src = m->vertices.data; */
	/* float const *const	srcend = src + m->width * m->vertices.size; */
	/* t_vertex_basic		tmp[1]; */

	/* if (ftv_reserve(v, m->vertices.size)) */
	/* 	sp_enomem(); */
	/* bzero(tmp, sizeof(*tmp)); */
	/* while (src < srcend) */
	/* { */
	/* 	memcpy(&tmp->pos, src + 0, sizeof(float) * 3); */
	/* 	if (m->width == 5 || m->width == 8) */
	/* 		memcpy(&tmp->tex, src + 3, sizeof(float) * 2); */
	/* 	if (m->width == 6) */
	/* 		memcpy(&tmp->nor, src + 3, sizeof(float) * 3); */
	/* 	else if (m->width == 8) */
	/* 		memcpy(&tmp->nor, src + 5, sizeof(float) * 3); */
	/* 	ftv_push_back_unsafe(v, tmp); */
	/* 	src += m->width; */
	/* } */
	return ;
}

static void	retreive_faces(t_objmodel const *const m, t_ftvector *const f)
{
	
	/* t_ui const			*src = m->faces.data; */
	/* t_ui const *const	srcend = src + 3 * m->faces.size; */
	/* t_ui				tmp[3]; */

	/* if (ftv_reserve(f, m->faces.size)) */
	/* 	sp_enomem(); */
	/* bzero(tmp, sizeof(*tmp)); */
	/* while (src < srcend) */
	/* { */
	/* 	memcpy(tmp, src, sizeof(t_ui) * 3); */
	/* 	ftv_push_back_unsafe(f, tmp); */
	/* 	src += 3; */
	/* } */
	return ;
}

static void	push_index(size_t const *ptrpad, void *beginptr, int i)
{
	*(t_ui*)(beginptr + *ptrpad) = (t_ui)i;
	return ;
}

void		op_retreive_data(t_objmodel const *m, t_vbo_basic *v, t_ftvector *f)
{
	size_t	ptrpad;

	ptrpad = m->width * sizeof(float) + sizeof(t_ftset_node);
	v->npos = 3;
	if (m->width == 5 || m->width == 8)
		v->ntex = 2;
	if (m->width == 6 || m->width == 8)
		v->nnor = 3;
	fts_foreachi(&m->vertices, &push_index, &ptrpad);
	retreive_vertices(m, &v->vertices);
	retreive_faces(m, f);
	return ;
}
