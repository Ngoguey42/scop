/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_fill1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/08 12:49:25 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/12 14:58:17 by ngoguey          ###   ########.fr       */
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

int			sp_meshfill_teapot1(t_env const *e, t_mesh *me, t_vbo_basic *vbo)
{
	t_objmodel				m[1];
	t_texture const *const	t = e->textures + sp_porcelain_texture;

	if (op_parse_obj(m, "res/teapot.obj"))
		return (ERROR("op_parse_obj(m)"), 1);
	op_retreive_data(m, vbo, &me->faces);
	sp_recenter_positions(vbo);
	sp_calc_normals(e, me, vbo);
	sp_calc_uv(e, vbo, (float[2]){(float)t->dim[0] / (float)t->dim[1], 2.f}
		, uvwrap_spherical);
	sp_clean_objmodel(m);
	return (0);
	(void)e;
	(void)me;
}

int			sp_meshfill_plane(t_env const *e, t_mesh *me, t_vbo_basic *vbo)
{
	t_objmodel				m[1];
	t_texture const *const	t = e->textures + sp_porcelain_texture;

	if (op_parse_obj(m, "res/teapot2.obj"))
		return (ERROR("op_parse_obj(m)"), 1);
	op_retreive_data(m, vbo, &me->faces);
	sp_recenter_positions(vbo);
	sp_calc_normals(e, me, vbo);
	sp_calc_uv(e, vbo, (float[2]){(float)t->dim[0] / (float)t->dim[1], 2.f}
		, uvwrap_spherical);
	sp_clean_objmodel(m);
	return (0);
	(void)e;
	(void)me;
}

int			sp_meshfill_ft(t_env const *e, t_mesh *me, t_vbo_basic *vbo)
{
	t_objmodel				m[1];
	t_texture const *const	t = e->textures + sp_porcelain_texture;

	if (op_parse_obj(m, "res/42.obj"))
		return (ERROR("op_parse_obj(m)"), 1);
	op_retreive_data(m, vbo, &me->faces);
	sp_recenter_positions(vbo);
	sp_calc_normals(e, me, vbo);
	sp_calc_uv(e, vbo, (float[2]){(float)t->dim[0] / (float)t->dim[1], 2.f}
		, uvwrap_spherical);
	sp_clean_objmodel(m);
	return (0);
	(void)e;
	(void)me;
}

int			sp_meshfill_csie(t_env const *e, t_mesh *me, t_vbo_basic *vbo)
{
	t_objmodel				m[1];

	if (op_parse_obj(m, "res/new_csie_b1.obj"))
		return (ERROR("op_parse_obj(m)"), 1);
	op_retreive_data(m, vbo, &me->faces);
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

/*
**  [[[end]]]
*/
