/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_fill2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/08 12:52:39 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/10 13:15:04 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "objmodel.h"
#include <math.h>
#include <string.h>

/*
**  [[[cog
**  import cog
**  cog.outl("*" "/")
**  from confloader import output_meshfill
**  output_meshfill(5)
**  cog.out("/" "*")
**  ]]]
*/

int			sp_meshfill_ptn(t_env const *e, t_mesh *me, t_vbo_basic *vbo)
{
	t_objmodel	m[1];

	if (op_parse_obj(m, "res/alfa147.obj"))
	return (ERROR("op_parse_obj(m)"), 1);
		op_retreive_data(m, vbo, &me->faces);
	sp_clean_objmodel(m);
	return (0);
	(void)e;
	(void)me;
}

int			sp_meshfill_sun(t_env const *e, t_mesh *me, t_vbo_basic *vbo)
{
	t_vertex_basic	vertices[8] = {
	BVERT_POS(-1.0f, 1.0f, -1.0f),
	BVERT_POS(-1.0f, -1.0f, -1.0f),
	BVERT_POS(-1.0f, 1.0f, 1.0f),
	BVERT_POS(-1.0f, -1.0f, 1.0f),
	BVERT_POS(1.0f, 1.0f, 1.0f),
	BVERT_POS(1.0f, -1.0f, 1.0f),
	BVERT_POS(1.0f, 1.0f, -1.0f),
	BVERT_POS(1.0f, -1.0f, -1.0f)
	};
	GLuint indices[36] = {
	0,1,2,2,1,3,
	4,5,6,6,5,7,
	3,1,5,5,1,7,
	0,2,6,6,2,4,
	6,7,0,0,7,1,
	2,3,4,4,3,5
	};
	vbo->npos = 3;
	(void)ftv_insert_range(
	&vbo->vertices, vertices, sizeof(vertices) / sizeof(*vertices));
	(void)ftv_insert_range(
	&me->faces, indices, sizeof(indices) / sizeof(*indices) / 3);
	return (0);
	(void)e;
	(void)me;
}

/*
**  [[[end]]]
*/
