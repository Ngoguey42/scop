/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_fill1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/08 12:49:25 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/10 13:14:34 by ngoguey          ###   ########.fr       */
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
**  output_meshfill(0)
**  cog.out("/" "*")
**  ]]]
*/

int			sp_meshfill_plane(t_env const *e, t_mesh *me, t_vbo_basic *vbo)
{
	t_objmodel				m[1];
	t_texture const *const	t = e->textures + sp_porcelain_texture;

	/* if (op_parse_obj(m, "res/cessna.obj")) */
	/* if (op_parse_obj(m, "res/teapot.obj")) */
	if (op_parse_obj(m, "res/teapot2.obj"))
	return (ERROR("op_parse_obj(m)"), 1);
	op_retreive_data(m, vbo, &me->faces);
	sp_calc_uv_plan_oxy(e, vbo, (float)t->dim[0] / (float)t->dim[1], 1.f);
	sp_calc_normals(e, me, vbo);
	sp_clean_objmodel(m);
	return (0);
	(void)e;
	(void)me;
}

int			sp_meshfill_square(t_env const *e, t_mesh *me, t_vbo_basic *vbo)
{
	t_vertex_basic	vertices[] = {

	BVERT_POSCOL( 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f),  // Top Right
	BVERT_POSCOL(0.5f, -0.5f, 2.0f,   0.0f, 1.0f, 0.0f),  // Bottom Right
	BVERT_POSCOL(-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f),  // Bottom Left
	BVERT_POSCOL(-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f),  // Top Left
        };
	GLuint			indices[] = {  // Note that we start from 0!
		3, 1, 0,  // First Triangle
		3, 2, 1   // Second Triangle
	};
	vbo->npos = 3;
	vbo->ncol = 3;
	(void)ftv_insert_range(
	&vbo->vertices, vertices, sizeof(vertices) / sizeof(*vertices));
	(void)ftv_insert_range(
	&me->faces, indices, sizeof(indices) / sizeof(*indices) / 3);
        sp_calc_normals(e, me, vbo);        
	return (0);
	(void)e;
	(void)me;
}

int			sp_meshfill_land(t_env const *e, t_mesh *me, t_vbo_basic *vbo)
{
	t_ftvector		lines[1];
	size_t const	line_points = (int)pow(2., (double)POINTS_DEPTHI);
	float			bounds[2];

	if (ftv_init_instance(lines, sizeof(float) * line_points))
	sp_enomem();
	if (ftv_insert_count(lines, lines->data, line_points))
	sp_enomem();
	sp_fill_landgrid(lines);
 	if (ftv_reserve(&vbo->vertices, lines->size * lines->size))
	sp_enomem();
	sp_fill_landvertices(lines, vbo, bounds);
	if (ftv_reserve(&me->faces, (lines->size - 1) * (lines->size - 1) * 2))
	sp_enomem();
	sp_fill_landfaces(lines, &me->faces);
	sp_fill_landrgb(vbo, bounds);
	ftv_release(lines, NULL);
		sp_calc_normals(e, me, vbo);
	return (0);
	(void)e;
	(void)me;
}

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
