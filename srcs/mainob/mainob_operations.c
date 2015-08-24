/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainob_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/16 11:57:44 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/24 17:23:09 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <string.h>

void		sp_mainob_model_remapuv(t_env *e, t_uvwrapping_type t)
{
	t_mesh					*me;
	t_texture const *const	tex = e->textures + sp_porcelain_texture;

	me = MEOFOB(e, e->mainob);
	if (me->usage == GL_STATIC_DRAW)
	{
		ERROR("Cannot remap uv for this mesh.");
		return ;
	}
	ftv_clear(&me->vertices, NULL);
	sp_calc_uv(e, &me->vbo
				, (float[2]){(float)tex->dim[0] / (float)tex->dim[1], 2.f}, t);
	sp_shrink_vbo(&me->vertices, &me->vbo);
	sp_refresh_vbo(e, me);
	return ;
}

void		sp_mainob_resetpos(t_env *e)
{
	t_ob		*ob;

	ob = e->mainob;
	ob->position = D_MAINOBPOS_V3;
	ob->rotation = D_MAINOBANGLES_V3;
	ob->moved = true;
	return ;
}

void		sp_mainob_changemodel(t_env *e, t_model_index moi)
{
	t_ob				*ob;
	t_program_index		pi_prev;
	t_program_index		pi_new;

	ob = e->mainob;
	pi_prev = MEOFOB(e, ob)->program;
	pi_new = MEOFMO(e, e->models + moi)->program;
	ob->model = moi;
	if (pi_prev != pi_new)
		ftl_splice_one_back(e->obs + pi_new, e->obs + pi_prev,
							(t_ftlist_node*)ob);
	return ;
}
