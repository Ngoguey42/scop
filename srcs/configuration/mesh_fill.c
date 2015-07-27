/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 15:57:45 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/27 18:30:49 by ngoguey          ###   ########.fr       */
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
	op_init_instance(m, "res/teapot.obj");
	if (op_parse_obj(m))
		return (ERROR("op_parse_obj(m)"), 1);
	op_swap_vectors(m, &me->vertices, &me->faces);
	sp_wrap_texture_planxy(&me->vertices, 1.8f, 442.f / 405.f);//porcelain
	/* (void)sp_wrap_texture_planxy(&me->vertices, 6.f, 1.f);//metal */
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
	/* (void)op_init_instance(m, "res/Pretty_House.obj"); */
	op_init_instance(m, "res/alfa147.obj");
	/* op_init_instance(m, "res/42.obj"); */
	if (op_parse_obj(m))
		return (ERROR("op_parse_obj(m)"), 1);
	/* sp_wrap_texture_planxy(m, 1.8f, 442.f / 405.f); */
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
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,    // Top Right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,    // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   // Bottom Left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   // Top Left 
	};
	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3,  // First Triangle
		1, 2, 3   // Second Triangle
	};

	ftv_init_instance(vert, sizeof(float) * 6);
	
	(void)ftv_insert_range(vert, vertices, 4);
	(void)ftv_insert_range(&me->faces, indices, 2);

	int	i;
	int width;
	int	j;
	
	width = 6;
	for (i = 0; i < (int)vert->size; i++)
	{
		qprintf("[%d]", i);
		for (j = 0; j < width; j++)
			qprintf("% .2f ", i,
					((float*)vert->data)[i * width + j]);
		qprintf("\n");
	}

	sp_normals_add(vert, &me->faces);
	width = 9;
	for (i = 0; i < (int)vert->size; i++)
	{
		qprintf("[%d]", i);
		for (j = 0; j < width; j++)
			qprintf("% .2f ", i,
					((float*)vert->data)[i * width + j]);
		qprintf("\n");
	}

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
	if (ftv_reserve(&me->vertices, lines->size * lines->size))
		sp_enomem();
	sp_fill_landvertices(lines, &me->vertices, bounds);
	if (ftv_reserve(&me->faces, (lines->size - 1) * (lines->size - 1) * 2))
		sp_enomem();
	sp_fill_landfaces(lines, &me->faces);
	sp_fill_landrgb(&me->vertices, bounds);
	ftv_release(lines, NULL);
	return (0);
	(void)e;
}
