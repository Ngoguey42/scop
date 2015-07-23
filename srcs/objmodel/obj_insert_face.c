/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_insert_face.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/23 11:05:53 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/23 11:34:26 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "objmodel_parsing.h"

#define TEXTURE(I) (((float*)m->textures.data) + 2 * (I))
#define NORMAL(I) (((float*)m->normals.data) + 3 * (I))

/*
** receiving a vertex of any size, gives index, may push it in vertices.
*/
static size_t	gen_vertex_index(t_objmodel *m, float const *vertex)
{
	int		i;

	i = ftv_find_index(&m->vertices, vertex);
	if (i < 0)
	{
		i = (int)m->vertices.size;
		if (ftv_push_back(&m->vertices, vertex))
			sp_enomem();
	}
	return (i);
}

#define COORD(I) (((float*)(m->coords.data)) + (3 * (I)))


/* #define COORD(I) */

/* ( */
/* 	((float*)(m->coords.data)) */
/* 	+ 3 * (I)) */
/* 	) */

/*
** receiving 3 indices for [0]coord/[1]texture/[2]normal
** building a vertex of any size
*/
static void		build_vertex(t_objmodel const *m, float vert[8],
							 size_t const indices[3])
{
c	/* T; */
	/* qprintf("indice %u\n", indices[0]); */

	/* qprintf("%u\n", sizeof(size_t)); */
	/* qprintf("%u\n", sizeof(void*)); */
	/* qprintf("%u\n", sizeof(unsigned int)); */
	
	/* qprintf("(((float*)%p) + 3 * (%u)) = %p\n", m->coords.data, indices[0], */
	/* 		/\* COORD(indices[0]) *\/ */
	/* 		(((float*)(m->coords.data)) + (3 * (0))) */
			
		/* ); */
	
	/* qprintf("size coordvert %u\n", m->coords.size); */
	/* qprintf("size coordvert %p\n", m->coords.data); */
	/* qprintf("diffptr %p\n", (void*)COORD(indices[0]) - m->coords.data); */
	/* qprintf("memcpy(%p, %p, %u)", vert, COORD(indices[0]), sizeof(float) * 3); */
	memcpy(vert, COORD(indices[0]), sizeof(float) * 3);
	/* T; */
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
	T;
	return ;
}

/*
** receiving indices in the right position:
** (coords at 0/3/6, textures at 1/4/7, normals at 2/5/8)
*/
void	op_insert_face(t_objmodel *m, size_t const oldind[9])
{
	size_t	newindices[3];
	float	vert[8];

	qprintf("addresse de vert %p\n", vert);
	qprintf("addresse de vert %p\n", &vert);
	T;
	build_vertex(m, vert, oldind);
	T;
	newindices[0] = gen_vertex_index(m, vert);
	T;
	build_vertex(m, vert, oldind + 3);
	newindices[1] = gen_vertex_index(m, vert);
	build_vertex(m, vert, oldind + 6);
	newindices[2] = gen_vertex_index(m, vert);
	T;
	if (ftv_push_back(&m->faces, newindices))
		sp_enomem();
	T;
	return ;
}
