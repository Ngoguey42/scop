/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_dumb_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/17 14:36:32 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/17 14:50:32 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int			sp_meshfillbumb_objmodel(t_env const *e, t_mesh *me
										, t_vbo_basic *vbo
										, char const *filename)
{
	t_objmodel				m[1];
	t_texture const *const	t = e->textures + sp_porcelain_texture;

	if (op_parse_obj(m, filename))
		return (ERROR("op_parse_obj(m)"), 1);
	op_retreive_data(m, vbo, &me->faces);
	sp_recenter_positions(vbo);
	if (vbo->nnor == 0)
		sp_calc_normals(e, me, vbo);
	if (vbo->ntex == 0)
		sp_calc_uv(e, vbo, (float[2]){(float)t->dim[0] / (float)t->dim[1], 2.f}
					, uvwrap_spherical);
	return (0);
}
