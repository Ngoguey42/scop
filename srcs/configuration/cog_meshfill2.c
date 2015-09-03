/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cog_meshfill2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/24 15:53:33 by ngoguey           #+#    #+#             */
/*   Updated: 2015/09/03 16:10:17 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "objmodel/objmodel.h"
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
/*
int			sp_meshfill_plane(t_env const *e, t_mesh *me, t_vbo_basic *vbo)
{
	return (sp_meshfillbumb_objmodel(e, me, vbo, "res/cessna.obj"));
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

int			sp_meshfill_sun(t_env const *e, t_mesh *me, t_vbo_basic *vbo)
{
	t_objmodel		m[1];

	if (op_parse_obj(m, "res/dodecahedron.obj"))
		return (ERROR("op_parse_obj(m)"), 1);
	op_retreive_data(m, vbo, &me->faces);
	return (0);
	(void)e;
	(void)me;
}
*/
/*
**  [[[end]]]
*/
