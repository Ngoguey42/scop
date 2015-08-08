/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_fill1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/08 12:49:25 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/08 12:50:34 by ngoguey          ###   ########.fr       */
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
**  from scop_confloader import output_meshfill
**  output_meshfill(0)
**  cog.out("/" "*")
**  ]]]
*/

int			sp_meshfill_plane(t_env const *e, t_mesh *me)
{
	t_objmodel	m[1];

	/* if (op_parse_obj(m, "res/cessna.obj")) */
	/* if (op_parse_obj(m, "res/teapot.obj")) */
	if (op_parse_obj(m, "res/teapot2.obj"))
		return (ERROR("op_parse_obj(m)"), 1);
	op_swap_vectors(m, &me->vertices, &me->faces);
	sp_inject_uv_plan_oxy(&me->vertices,
				e->textures + sp_porcelain_texture, 2.0f, 3);
	sp_inject_normals(&me->vertices, &me->faces);
	sp_clean_objmodel(m);
	return (0);
	(void)e;
	(void)me;
}

int			sp_meshfill_square(t_env const *e, t_mesh *me)
{
	t_ftvector		vert[1];

	GLfloat vertices[] = {
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // Top Right
		 0.5f, -0.5f, 2.0f,   0.0f, 1.0f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  // Bottom Left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  // Top Left
	};
	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3,  // First Triangle
		1, 2, 3   // Second Triangle
	};
	(void)ftv_init_instance(vert, sizeof(float) * 6);
	(void)ftv_insert_range(vert, vertices, 4);
	(void)ftv_insert_range(&me->faces, indices, 2);
	sp_inject_normals(vert, &me->faces);
	memcpy(&me->vertices, vert, sizeof(t_ftvector));
	return (0);
	(void)e;
	(void)me;
}

int			sp_meshfill_land(t_env const *e, t_mesh *me)
{
	t_ftvector		lines[1];
	size_t const	line_points = (int)pow(2., (double)POINTS_DEPTHI);
	float			bounds[2];

	if (ftv_init_instance(lines, sizeof(float) * line_points))
		sp_enomem();
	if (ftv_insert_count(lines, lines->data, line_points))
		sp_enomem();
	sp_fill_landgrid(lines);
	//fuite sur me->vertices
 	if (ftv_init_instance(&me->vertices, 6 * sizeof(float)))
		sp_enomem();
 	if (ftv_reserve(&me->vertices, lines->size * lines->size))
		sp_enomem();
	sp_fill_landvertices(lines, &me->vertices, bounds);
	if (ftv_reserve(&me->faces, (lines->size - 1) * (lines->size - 1) * 2))
		sp_enomem();
	sp_fill_landfaces(lines, &me->faces);
	sp_fill_landrgb(&me->vertices, bounds);
	ftv_release(lines, NULL);
	sp_inject_normals(&me->vertices, &me->faces);
	return (0);
	(void)e;
	(void)me;
}

int			sp_meshfill_ptn(t_env const *e, t_mesh *me)
{
	t_objmodel	m[1];

	/* if (op_parse_obj(m, "res/new_csie_b1.obj")) */
	/* if (op_parse_obj(m, "res/42.obj")) */
	if (op_parse_obj(m, "res/alfa147.obj"))
		return (ERROR("op_parse_obj(m)"), 1);
	/* sp_inject_uv_plan_oxy(m, 1.8f, 442.f / 405.f); */
	op_swap_vectors(m, &me->vertices, &me->faces);
	sp_clean_objmodel(m);
	return (0);
	(void)e;
	(void)me;
}

int			sp_meshfill_sun(t_env const *e, t_mesh *me)
{
	GLfloat vertices[24] = {
		-1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f
	};
	GLuint indices[36] = {
		0,1,2,2,1,3,
		4,5,6,6,5,7,
		3,1,5,5,1,7,
		0,2,6,6,2,4,
		6,7,0,0,7,1,
		2,3,4,4,3,5
	};
	(void)ftv_insert_range(
		&me->vertices, vertices, sizeof(vertices) / sizeof(*vertices) / 3);
	(void)ftv_insert_range(
		&me->faces, indices, sizeof(indices) / sizeof(*indices) / 3);
	return (0);
	(void)e;
	(void)me;
}

/*
**  [[[end]]]
*/
