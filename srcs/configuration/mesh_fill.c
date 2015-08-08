/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 15:57:45 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/08 09:32:07 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "objmodel.h"
#include <math.h>
#include <string.h>

int				sp_meshfill_plane(t_env const *e, t_mesh *me)
{
	t_objmodel	m[1];
	/* op_init_instance(m, "res/teapot2.obj"); */

	/* (void)op_init_instance(m, "res/cessna.obj"); */
	/* if (op_init_instance(m, "res/teapot.obj") */
	if (op_parse_obj(m, "res/teapot2.obj"))
		return (ERROR("op_parse_obj(m)"), 1);
	op_swap_vectors(m, &me->vertices, &me->faces);
	sp_inject_uv_plan_oxy(&me->vertices,
				e->textures + sp_porcelain_texture, 2.0f, 3);
	sp_inject_normals(&me->vertices, &me->faces);
	sp_clean_objmodel(m);
	(void)e;
	(void)me;
	/* ft_leaks(); */
	return (0);
}

int				sp_meshfill_item2(t_env const *e, t_mesh *me)
{
	t_objmodel	m[1];

	/* op_init_instance(m, "res/new_csie_b1.obj"); */
	/* op_init_instance(m, "res/cessna.obj"); */
	/* op_init_instance(m, "res/alfa147.obj"); */
	/* op_init_instance(m, "res/42.obj"); */
	/* if (op_parse_obj(m, "res/cessna.obj")) */
	/* if (op_parse_obj(m, "res/alfa147.obj")) */
	if (op_parse_obj(m, "res/new_csie_b1.obj"))
		return (ERROR("op_parse_obj(m)"), 1);
	/* sp_inject_uv_plan_oxy(m, 1.8f, 442.f / 405.f); */
	op_swap_vectors(m, &me->vertices, &me->faces);
	sp_clean_objmodel(m);
	(void)e;
	(void)me;
	return (0);
}

int				sp_meshfill_square(t_env const *e, t_mesh *me)
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

	ftv_init_instance(vert, sizeof(float) * 6);
	
	(void)ftv_insert_range(vert, vertices, 4);
	(void)ftv_insert_range(&me->faces, indices, 2);

	

	sp_inject_normals(vert, &me->faces);
	
	memcpy(&me->vertices, vert, sizeof(t_ftvector));
	

	(void)e;
	(void)me;
	return (0);
}

int				sp_meshfill_land(t_env const *e, t_mesh *me)
{
	t_ftvector		lines[1];
	size_t const	line_points = (int)pow(2., (double)POINTS_DEPTHI);
	float			bounds[2];

	if (ftv_init_instance(lines, sizeof(float) * line_points))
		sp_enomem();
	if (ftv_insert_count(lines, lines->data, line_points))
		sp_enomem();
	sp_fill_landgrid(lines);
	//fuite
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

	/* qprintf("%u %u\n", me->vertices.chunk_size, me->vertices.size); */

	qprintf("%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f \n",
			((float*)me->vertices.data)[0],
			((float*)me->vertices.data)[1],
			((float*)me->vertices.data)[2],
			((float*)me->vertices.data)[3],
			((float*)me->vertices.data)[4],
			((float*)me->vertices.data)[5],
			((float*)me->vertices.data)[6],
			((float*)me->vertices.data)[7],
			((float*)me->vertices.data)[8]
		);
	

	
	sp_inject_normals(&me->vertices, &me->faces);
	/* qprintf("%u %u\n", me->vertices.chunk_size, me->vertices.size); */

	qprintf("%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f \n",
			((float*)me->vertices.data)[0],
			((float*)me->vertices.data)[1],
			((float*)me->vertices.data)[2],
			((float*)me->vertices.data)[3],
			((float*)me->vertices.data)[4],
			((float*)me->vertices.data)[5],
			((float*)me->vertices.data)[6],
			((float*)me->vertices.data)[7],
			((float*)me->vertices.data)[8]
		);
	
	/* return (1); */

	
	return (0);
	(void)e;
}

int				sp_meshfill_sun(t_env const *e, t_mesh *me)
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
}
