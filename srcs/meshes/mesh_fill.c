/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 15:57:45 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/21 16:31:32 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "objmodel.h"
#include <math.h>

int				sp_meshfill_item(t_env const *e, t_mesh *me)
{
	t_objmodel	m[1];

	op_init_instance(m, "res/teapot2.obj");
	if (op_parse_obj(m))
		return (ERROR("op_parse_obj(m)"), 1);
	sp_wrap_texture_planxy(m, 1.8f, 442.f / 405.f);
	op_swap_vectors(m, &me->vertices, &me->faces);
	(void)e;
	(void)me;
	return (0);
}

int				sp_meshfill_square(t_env const *e, t_mesh *me)
{
	GLfloat vertices[] = {
		0.5f,  0.5f, 0.0f,  // Top Right
		0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
		-0.5f,  0.5f, 0.0f   // Top Left
	};
	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3,  // First Triangle
		1, 2, 3   // Second Triangle
	};

	ftv_push_backn(&me->vertices, vertices, 4);
	ftv_push_backn(&me->faces, indices, 2);
	(void)e;
	(void)me;
	return (0);
}

int				sp_meshfill_land(t_env const *e, t_mesh *me)
{
	t_ftvector		lines[1];
	size_t const	line_points = (int)pow(2., (double)POINTS_DEPTHI);

	if (ftv_init_instance(lines, sizeof(float) * line_points))
		sp_enomem();
	ftv_insert(lines, lines->data, line_points);
	sp_fill_landgrid(lines);
	sp_fill_landvertices(lines, &me->vertices);
	sp_fill_landfaces(lines, &me->faces);	
	return (0);
}
