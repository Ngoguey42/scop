/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_insert_face.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/23 11:05:53 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/08 10:56:33 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "objmodel_parsing.h"

#define PLAN(I) (((float*)(m->coords.data)) + (3 * (I)))
#define TEXTURE(I) (((float*)m->textures.data) + 2 * (I))
#define NORMAL(I) (((float*)m->normals.data) + 3 * (I))

/*
** 'op_insert_face'		receives indices in the right order.
** 							(plan 0/3/6, texture 1/4/7, normal 2/5/8)
** 							pushes them in ->vertices, ->faces
** **
** 'build_vertex'		receives 3 indices for [0]plan/[1]texture/[2]normal
** 							builds vert[8]
** **
** 'gen_vertex_index'	receives a vertex pointer, returns it's index
**							(may create it's index)
** *
**	'if (m->width != 8 && m->width != 6)'
**		UGLY LVL 9000
*/

static size_t	gen_vertex_index(t_objmodel *m, float const *vertex)
{
	int		i;

	i = -1;
	if (m->width != 8 && m->width != 6)
		i = ftv_find_index(&m->vertices, vertex);
	if (i < 0)
	{
		i = (int)m->vertices.size;
		if (ftv_push_back(&m->vertices, vertex))
			sp_enomem();
	}
	return (i);
}

static void		build_vertex(t_objmodel const *m, float vert[8],
							t_ui const indices[3])
{
	memcpy(vert, PLAN(indices[0]), sizeof(float) * 3);
	if (m->width == 5)
	{
		memcpy(vert + 3, TEXTURE(indices[1]), sizeof(float) * 2);
	}
	else if (m->width == 6)
	{
		memcpy(vert + 3, NORMAL(indices[2]), sizeof(float) * 3);
	}
	else if (m->width == 8)
	{
		memcpy(vert + 3, TEXTURE(indices[1]), sizeof(float) * 2);
		memcpy(vert + 5, NORMAL(indices[2]), sizeof(float) * 3);
	}
	return ;
}

void			op_insert_face(t_objmodel *m, t_ui const oldind[9])
{
	unsigned int	newindices[3];
	float			vert[8];

	build_vertex(m, vert, oldind);
	newindices[0] = gen_vertex_index(m, vert);
	build_vertex(m, vert, oldind + 3);
	newindices[1] = gen_vertex_index(m, vert);
	build_vertex(m, vert, oldind + 6);
	newindices[2] = gen_vertex_index(m, vert);
	if (ftv_push_back(&m->faces, newindices))
		sp_enomem();
	return ;
}
