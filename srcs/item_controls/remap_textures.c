/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remap_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/15 11:08:31 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/16 11:35:34 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <string.h>

void		sp_mainob_model_remapuv(t_env *e, t_uvwrapping_type t)
{
	t_mesh					*me;
	t_texture const *const  tex = e->textures + sp_porcelain_texture;

	me = MEOFOB(e, e->mainob);
	ftv_clear(&me->vertices, NULL);
	sp_calc_uv(e, &me->vbo
			   , (float[2]){(float)tex->dim[0] / (float)tex->dim[1], 2.f}, t);
	sp_shrink_vbo(&me->vertices, &me->vbo);
	sp_refresh_vbo(e, me);
	return ;
}
