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

int			sp_meshfill_plane(t_env const *e, t_mesh *me, t_vbo_basic *vbo)
{
	t_objmodel	m[1];

	/* if (op_parse_obj(m, "res/cessna.obj")) */
	/* if (op_parse_obj(m, "res/teapot.obj")) */
	if (op_parse_obj(m, "res/teapot2.obj"))
		return (ERROR("op_parse_obj(m)"), 1);
        op_retreive_data(m, vbo, &me->faces);
        sp_calc_uv_plan_oxy(e, me, vbo);
        sp_calc_normals(e, me, vbo);
	sp_clean_objmodel(m);
	return (0);
	(void)e;
	(void)me;
}

/*
**  [[[end]]]
*/
